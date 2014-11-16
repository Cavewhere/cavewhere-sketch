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

//Our includes
class cwTabletGraphicsView;

class cwMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit cwMainWindow(QWidget *parent = 0);

signals:

public slots:

private:
    cwTabletGraphicsView* GraphicsView;


};

#endif // CWMAINWINDOW_H
