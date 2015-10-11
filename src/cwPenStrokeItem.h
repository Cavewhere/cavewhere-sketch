/**************************************************************************
**
**    Copyright (C) 2014 by Philip Schuchardt
**    www.cavewhere.com
**
**************************************************************************/


#ifndef CWPENSTROKEITEM_H
#define CWPENSTROKEITEM_H

//Qt includes
#include <QGraphicsItem>
#include <QLineF>

//Our includes
#include "cwPenStroke.h"

class cwPenStrokeItem : public QGraphicsItem
{
public:
    cwPenStrokeItem();

    void setPenStroke(const cwPenStroke& stroke);
    cwPenStroke penStroke() const;

    void appendSegement(const cwPenSegment& segement);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:

    cwPenStroke Stroke;
    QRectF BoundingBox;
    QVector<QPolygonF> Segments;

    void updateBoundingBox();
    void updateSegements();
    void appendSegementAt(int index);

    QLineF perpendicularLineAt(int index) const;

};

#endif // CWPENSTROKEITEM_H
