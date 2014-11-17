/**************************************************************************
**
**    Copyright (C) 2014 by Philip Schuchardt
**    www.cavewhere.com
**
**************************************************************************/


#ifndef CWMAINWINDOW_H
#define CWMAINWINDOW_H

//Qt includes
#include <QMainWindow>

//For bluetooth testing
#include <QBluetoothServiceDiscoveryAgent>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothSocket>

//Our includes
class cwTabletGraphicsView;

class cwMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit cwMainWindow(QWidget *parent = 0);

signals:

public slots:
    //For bluetooth testing
    void addDevice(const QBluetoothDeviceInfo& info);
    void deviceDiscoveryFinished();
    void deviceDiscoveryCanceled();
    void handleDeviceDiscoveryError(QBluetoothDeviceDiscoveryAgent::Error error);

    void addService(const QBluetoothServiceInfo& service);
    void serviceDiscoveryFinished();
    void serviecDiscoveryCanceled();
    void handleServiceDiscoveryError(QBluetoothServiceDiscoveryAgent::Error error);

    void socketConnected();
    void readNewData();
    void handleSocketError(QBluetoothSocket::SocketError error);
    void handleStateChanged(QBluetoothSocket::SocketState state);

private:
    cwTabletGraphicsView* GraphicsView;

    //For bluetooth testing
    QBluetoothServiceDiscoveryAgent* BluetoothServiceAgent;
    QBluetoothDeviceDiscoveryAgent* BluetoothDeviceAgent;
    QBluetoothSocket* Socket;

    void processDistoX2Data(QByteArray &data);
    void sendDistoX2AcknowledgeByte(quint8 type);
    double distoX2RotationToDegrees(int rotation) const;
};

#endif // CWMAINWINDOW_H
