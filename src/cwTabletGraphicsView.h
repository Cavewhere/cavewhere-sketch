/**************************************************************************
**
**    Copyright (C) 2014 by Philip Schuchardt
**    www.cavewhere.com
**
**************************************************************************/


#ifndef CWTABLETGRAPHICSVIEW_H
#define CWTABLETGRAPHICSVIEW_H

//Qt includes
#include <QGraphicsView>

//Our includes
class cwSketchModel;
class cwSketchView;

class cwTabletGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit cwTabletGraphicsView(QWidget *parent = 0);

signals:

public slots:

protected:
    void tabletEvent(QTabletEvent* event);
    void resizeEvent(QResizeEvent* event);

private:
    //For testing
    cwSketchModel* SketchModel;
    cwSketchView* SketchView;

};

#endif // CWTABLETGRAPHICSVIEW_H
