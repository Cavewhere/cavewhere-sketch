/**************************************************************************
**
**    Copyright (C) 2014 by Philip Schuchardt
**    www.cavewhere.com
**
**************************************************************************/

//Our includes
#include "cwMainWindow.h"
#include "cwTabletGraphicsView.h"


//Qt includes
#include <QGraphicsScene>
#include <QDebug>

//Std includes
#include <math.h>


cwMainWindow::cwMainWindow(QWidget *parent) :
    QMainWindow(parent),
    GraphicsView(new cwTabletGraphicsView())
{
    setCentralWidget(GraphicsView);

    BluetoothDeviceAgent = new QBluetoothDeviceDiscoveryAgent(this);
    connect(BluetoothDeviceAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
            this, SLOT(addDevice(QBluetoothDeviceInfo)));
    connect(BluetoothDeviceAgent, SIGNAL(finished()),
            this, SLOT(deviceDiscoveryFinished()));
    connect(BluetoothDeviceAgent, SIGNAL(canceled()),
            this, SLOT(deviceDiscoveryCanceled()));
    connect(BluetoothDeviceAgent, SIGNAL(error(QBluetoothDeviceDiscoveryAgent::Error)),
            this, SLOT(handleDeviceDiscoveryError(QBluetoothDeviceDiscoveryAgent::Error)));

    BluetoothServiceAgent = new QBluetoothServiceDiscoveryAgent(this);
    connect(BluetoothServiceAgent, SIGNAL(serviceDiscovered(QBluetoothServiceInfo)),
            this, SLOT(addService(QBluetoothServiceInfo)));
    connect(BluetoothServiceAgent, SIGNAL(finished()),
            this, SLOT(serviceDiscoveryFinished()));
    connect(BluetoothDeviceAgent, SIGNAL(canceled()),
            this, SLOT(serviecDiscoveryCanceled()));
    connect(BluetoothDeviceAgent, SIGNAL(error(QBluetoothDeviceDiscoveryAgent::Error)),
            this, SLOT(handleServiceDiscovery(QBluetoothServiceDiscoveryAgent::Error)));

    Socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this);
    connect(Socket, SIGNAL(connected()), this, SLOT(socketConnected()));
    connect(Socket, SIGNAL(readyRead()), this, SLOT(readNewData()));
    connect(Socket, SIGNAL(error(QBluetoothSocket::SocketError)),
            this, SLOT(handleSocketError(QBluetoothSocket::SocketError)));
    connect(Socket, SIGNAL(stateChanged(QBluetoothSocket::SocketState)),
            this, SLOT(handleStateChanged(QBluetoothSocket::SocketState)));

    qDebug() << "Start looking for devices!";
    BluetoothDeviceAgent->start();

    qDebug() << "Looking for services";
    BluetoothServiceAgent->start();
}

/**
 * @brief cwMainWindow::addDevice
 * @param info
 */
void cwMainWindow::addDevice(const QBluetoothDeviceInfo &info)
{
    qDebug() << "Blue tooth device detected:" << info.name() << info.address().toString();
}

/**
 * @brief cwMainWindow::deviceDiscoveryFinished
 */
void cwMainWindow::deviceDiscoveryFinished()
{
    qDebug() << "Finished discovering devices!";
}


/**
 * @brief cwMainWindow::deviceDiscoveryCanceled
 */
void cwMainWindow::deviceDiscoveryCanceled()
{
    qDebug() << "Cancelled!";
}

/**
 * @brief cwMainWindow::handleError
 * @param error
 */
void cwMainWindow::handleDeviceDiscoveryError(QBluetoothDeviceDiscoveryAgent::Error error)
{
    qDebug() << "Bluetooth discovery error" << error;
}

/**
 * @brief cwMainWindow::addService
 * @param service
 */
void cwMainWindow::addService(const QBluetoothServiceInfo &service)
{
    qDebug() << "Service added:" << service.serviceUuid() << service.device().name() << service.device().address();

    if(service.device().name() == "DistoX-2542") {
        qDebug() << "\tName:" << service.serviceName();
        qDebug() << "\tDescription:" << service.serviceDescription();
        qDebug() << "\tIsComplete:" << service.isComplete();
        qDebug() << "\tIsRegistered:" << service.isRegistered();
        qDebug() << "\tIsValid:" << service.isValid();
        qDebug() << "\tsocketProtocol:" << service.socketProtocol();
        qDebug() << "\tserverChannel:" << service.serverChannel();

        Socket->connectToService(service);
    }

}

/**
 * @brief cwMainWindow::serviceDiscoveryFinished
 */
void cwMainWindow::serviceDiscoveryFinished()
{
    qDebug() << "Service discovery finished";
}

/**
 * @brief cwMainWindow::serviecDiscoveryCanceled
 */
void cwMainWindow::serviecDiscoveryCanceled()
{
    qDebug() << "Service discovery canceled";
}

/**
 * @brief cwMainWindow::handleServiceDiscovery
 * @param error
 */
void cwMainWindow::handleServiceDiscoveryError(QBluetoothServiceDiscoveryAgent::Error error)
{
    qDebug() << "Service discovery error:" << error;
}

/**
 * @brief cwMainWindow::socketConnected
 */
void cwMainWindow::socketConnected()
{
    qDebug() << "Socket connected!";
}

/**
 * @brief cwMainWindow::readNewData
 */
void cwMainWindow::readNewData()
{
   qDebug() << "Reading new data";
   qDebug() << "\tByte's avalible:" << Socket->bytesAvailable();
   QByteArray newData = Socket->readAll();
   qDebug() << "\tData:" << newData;

   processDistoX2Data(newData);

}

/**
 * @brief cwMainWindow::handleSocketError
 * @param error
 */
void cwMainWindow::handleSocketError(QBluetoothSocket::SocketError error)
{
    qDebug() << "Bluetooth socket error" << error << Socket->errorString();
}

/**
 * @brief cwMainWindow::handleStateChanged
 * @param state
 */
void cwMainWindow::handleStateChanged(QBluetoothSocket::SocketState state)
{
    qDebug() << "Bluetooth state changed:" << state;
}

/**
 * @brief cwMainWindow::processDistoX2Data
 * @param data
 */
void cwMainWindow::processDistoX2Data(QByteArray &data)
{
    if(data.size() != 8) {
        //TODO: Raise an error that the size isn't 8 bytes
        return;
    }

    quint8* input = reinterpret_cast<quint8*>(data.data()); // input buffer

    //TODO: Make these non-static
    static int oldType = 0;
    static int oldX = 0;
    static int oldY = 0;
    static int oldZ = 0; // previous packet

    int azimuth = 0;
    int distance = 0;
    int inclination = 0;
    int roll = 0;

    quint8 type = input[0];
    int op = type & 0x3F;
    if (op < 0x20) { // data packet
        sendDistoX2AcknowledgeByte(type); // send acknowledge byte
        int x = input[1] + (input[2] << 8);
        int y = input[3] + (input[4] << 8);
        int z = input[5] + (input[6] << 8);
        if (type != oldType && x != oldX && y != oldY && z != oldZ) {
            if (op == 1) { // survey data
                // 17 bit distance
                distance = x + ((type & 0x40) << 10);
                // cm resolution above 100m
                if (distance > 100000) {
                    distance = (distance - 90000) * 10;
                }

                azimuth = y;
                inclination = z;
                roll = input[7] << 8; // high bits of roll angle

                qDebug() << "\tDistance:" << distance / 1000.0 << "Azimuth" << distoX2RotationToDegrees(azimuth) << "clino" << distoX2RotationToDegrees(inclination) << "roll" << distoX2RotationToDegrees(roll);
            } else if (op == 4) { // vector data
                int absG = x; // absolute value of G vector
                int absM = y; // absolute value of M vector
                int dip = z; // dip angle
                roll += input[7]; // low bits of roll angle
                qDebug() << "\tVector data:" << absG << absM << dip << roll;
            } else if (op == 2) { // G calibration data
                int Gx = x; // acceleration x sensor
                int Gy = y; // acceleration y sensor
                int Gz = z; // acceleration z sensor
                qDebug() << "\tG calibration data:" << Gx << Gy << Gz;
            } else if (op == 3) { // M calibration data
                int Mx = x; // magnetic x sensor
                int My = y; // magnetic y sensor
                int Mz = z; // magnetic z sensor
                qDebug() << "\tM calibration data:" << Mx << My << Mz;
            }
            // ignore unknown packets
            oldType = type; oldX = x; oldY = y; oldZ = z;
        }
    }
}

/**
 * @brief cwMainWindow::sendDistoX2AcknowledgeByte
 * @param type
 */
void cwMainWindow::sendDistoX2AcknowledgeByte(quint8 type)
{
    quint8 acknowlegdeByte = (type & 0x80) | 0x55;
    Socket->write(reinterpret_cast<const char*>(&acknowlegdeByte), 1);
}

double cwMainWindow::distoX2RotationToDegrees(int rotation) const
{
    const static double pi = acos(-1);
    double rotationInRad = rotation * pi / 32768.0;
    double rotationInDeg = rotationInRad * 180.0 / pi;
    return rotationInDeg;
}

