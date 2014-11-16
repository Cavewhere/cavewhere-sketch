/**************************************************************************
**
**    Copyright (C) 2014 by Philip Schuchardt
**    www.cavewhere.com
**
**************************************************************************/

//Qt includes
#include <QGuiApplication>
#include <QApplication>

//Our includes
#include "cwMainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    cwMainWindow mainWindow;
    mainWindow.show();

    return a.exec();
}

