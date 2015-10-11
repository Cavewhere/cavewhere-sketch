/**************************************************************************
**
**    Copyright (C) 2014 by Philip Schuchardt
**    www.cavewhere.com
**
**************************************************************************/


//Our includes
#include "cwPenStrokeItem.h"
#include "cwPenSegment.h"

//Qt includes
#include <QPainter>
#include <QDebug>

cwPenStrokeItem::cwPenStrokeItem()
{
}

/**
 * @brief cwPenStrokeItem::setPenStroke
 * @param stroke
 */
void cwPenStrokeItem::setPenStroke(const cwPenStroke &stroke)
{
    Stroke = stroke;
    updateSegements();
}

/**
 * @brief cwPenStrokeItem::penStroke
 * @return
 */
cwPenStroke cwPenStrokeItem::penStroke() const
{
    return Stroke;
}

/**
 * @brief cwPenStrokeItem::insertSegements
 * @param beforeIndex
 * @param segements
 */
void cwPenStrokeItem::appendSegement(const cwPenSegment& segement)
{
    Stroke.append(segement);

    if(Stroke.numberOfSegments() <= 1) {
        return;
    }

    appendSegementAt(Stroke.numberOfSegments() - 2);

    updateBoundingBox();
}

/**
 * @brief cwPenStrokeItem::boundingRect
 * @return Returns the current bounding box of the item
 */
QRectF cwPenStrokeItem::boundingRect() const
{
    return BoundingBox;
}

/**
 * @brief cwPenStrokeItem::paint
 * @param painter
 * @param option
 * @param widget
 */
void cwPenStrokeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Stroke.color());
    foreach(QPolygonF polygon, Segments) {
        painter->drawPolygon(polygon);
    }
}

/**
 * @brief cwPenStrokeItem::updateBoundingBox
 *
 * This will update the cached bounding box of the stroke item
 */
void cwPenStrokeItem::updateBoundingBox()
{
    prepareGeometryChange();

    QRectF boundingBox;
    foreach(QPolygonF polygon, Segments) {
        QRectF polygonBox = polygon.boundingRect();
        boundingBox = boundingBox.united(polygonBox);
    }

    BoundingBox = boundingBox;
}

/**
 * @brief cwPenStrokeItem::updateSegements
 *
 * This will update the pen stroke segements.
 */
void cwPenStrokeItem::updateSegements()
{
    Segments.clear();

    if(Stroke.numberOfSegments() <= 1) {
        return;
    }

    //Go through the segments from left to right
    for(int i = 0; i < Stroke.numberOfSegments() - 1; ++i) {
        appendSegementAt(i);
    }

    updateBoundingBox();
}

/**
 * @brief cwPenStrokeItem::appendSegementAt
 * @param index
 */
void cwPenStrokeItem::appendSegementAt(int index)
{
    QLineF l0 = perpendicularLineAt(index);
    QLineF l1 = perpendicularLineAt(index + 1);

    QPolygonF polygon;
    polygon.append(l0.p1());
    polygon.append(l0.p2());
    polygon.append(l1.p2());
    polygon.append(l1.p1());

    Segments.append(polygon);
}

/**
 * @brief cwPenStrokeItem::segmentNormalLine
 * @param index
 * @return
 *
 * This calculates the perpendicular line between pen segments.
 */
QLineF cwPenStrokeItem::perpendicularLineAt(int index) const
{
    Q_ASSERT(index >= 0);
    Q_ASSERT(index < Stroke.numberOfSegments());

    cwPenSegment left = index - 1 < 0 ? cwPenSegment() : Stroke.segment(index - 1);
    cwPenSegment mid = Stroke.segment(index);
    cwPenSegment right = index + 1 >= Stroke.numberOfSegments() ? cwPenSegment() : Stroke.segment(index + 1);

    QLineF topLine;
    QLineF bottomLine;

    double halfWidth = mid.width() * 0.5;

//    qDebug() << "Null?:" << !left.isNull() << !right.isNull();
    if(!left.isNull() && !right.isNull()) {
        //A middle segment
        QLineF leftLine(mid.point(), left.point());
        QLineF rightLine(mid.point(), right.point());
        double angleBetween = leftLine.angleTo(rightLine);
        double halfAngle = angleBetween * 0.5;

//        qDebug() << "Both good!";

        topLine.setP1(mid.point());
        topLine.setAngle(leftLine.angle() + halfAngle);
        topLine.setLength(halfWidth);

        bottomLine.setP1(mid.point());
        bottomLine.setAngle(leftLine.angle() + halfAngle);
        bottomLine.setLength(-halfWidth);

        Q_ASSERT(topLine.p1() == bottomLine.p1());
        Q_ASSERT(topLine.p2() != bottomLine.p2());
    } else {
        QLineF line;
        if(!left.isNull()) {
            //The start section
            line = QLineF(mid.point(), right.point());
//            qDebug() << "left good:" << line;
        } else if(!right.isNull()) {
            line = QLineF(mid.point(), left.point());
//            qDebug() << "Right good:" << line;
        }

        QLineF normalLine = line.normalVector();
//        qDebug() << "NormalLine:" << normalLine;

        topLine = normalLine;
        topLine.setLength(halfWidth);

        bottomLine = normalLine;
        bottomLine.setLength(-halfWidth);

        Q_ASSERT(topLine.p1() == bottomLine.p1());
//        Q_ASSERT(topLine.p2() != bottomLine.p2());
    }


    return QLineF(topLine.p2(), bottomLine.p2());
}
