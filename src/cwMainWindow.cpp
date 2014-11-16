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

cwMainWindow::cwMainWindow(QWidget *parent) :
    QMainWindow(parent),
    GraphicsView(new cwTabletGraphicsView())
{
    setCentralWidget(GraphicsView);
}
