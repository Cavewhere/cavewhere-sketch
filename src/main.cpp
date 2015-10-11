/**************************************************************************
**
**    Copyright (C) 2014 by Philip Schuchardt
**    www.cavewhere.com
**
**************************************************************************/

//Qt includes
#include <QGuiApplication>
#include <QApplication>
#include <QTouchDevice>

//Our includes
#include "cwMainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QList<const QTouchDevice*> devices = QTouchDevice::devices();
    qDebug() << "Number of touch devices:" << devices.size();
    foreach(const QTouchDevice* device, devices) {
        qDebug() << "device:" << device;
    }

    cwMainWindow mainWindow;
    mainWindow.show();

    return a.exec();
}

