/**************************************************************************
**
**    Copyright (C) 2014 by Philip Schuchardt
**    www.cavewhere.com
**
**************************************************************************/

//Our includes
#include "cwTabletGraphicsView.h"
#include "cwSketchModel.h"
#include "cwSketchView.h"

//Qt includes
#include <QTabletEvent>
#include <QDebug>

cwTabletGraphicsView::cwTabletGraphicsView(QWidget *parent) :
    QGraphicsView(parent),
    SketchModel(new cwSketchModel(this)),
    SketchView(new cwSketchView(this))
{
    QGraphicsScene* scene = new QGraphicsScene(this);
    scene->addEllipse(QRect(QPoint(0, 0), QSize(10, 10)));
    setScene(scene);

    SketchView->setScene(scene);
    SketchView->setSketchModel(SketchModel);

    setRenderHints(QPainter::Antialiasing);
}

/**
 * @brief cwTabletGraphicsView::tabletEvent
 * @param event
 */
void cwTabletGraphicsView::tabletEvent(QTabletEvent *event)
{
    qreal pressure = event->pressure();
    qreal width = pressure * 2.0;
    cwPenSegment segment(event->posF(), width);

    switch (event->type()) {
    case QEvent::TabletPress:
        SketchModel->addStroke(cwPenStroke());
        SketchModel->addToLastStroke(segment);

        break;
    case QEvent::TabletRelease:
        break;
    case QEvent::TabletMove:
        SketchModel->addToLastStroke(segment);

        break;
    default:
        break;
    }
}

/**
 * @brief cwTabletGraphicsView::resizeEvent
 * @param event
 */
void cwTabletGraphicsView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);

    scene()->setSceneRect(QRectF(QPointF(), QSizeF(event->size())));

}
