/**************************************************************************
**
**    Copyright (C) 2014 by Philip Schuchardt
**    www.cavewhere.com
**
**************************************************************************/


#include "cwPenSegment.h"

//Qt includes
#include <QSharedData>
#include <QPointF>

class cwPenSegmentData : public QSharedData {
public:

    cwPenSegmentData(QPointF point,
                     double width) :
        Point(point),
        Width(width)
    { }

    cwPenSegmentData() :
        Width(-1.0)
    {}

    QPointF Point;
    double Width;
};

/**
 * @brief cwPenSegment::cwPenSegment
 *
 * Creates an null pen segment
 */
cwPenSegment::cwPenSegment() : d(new cwPenSegmentData)
{
}

/**
 * @brief cwPenSegment::cwPenSegment
 * @param p1
 * @param p2
 * @param width
 *
 * Creates a pen segment with p1 as the first point and
 * width of the segment.
 */
cwPenSegment::cwPenSegment(QPointF point, double width) :
    d(new cwPenSegmentData(point, width))
{
    Q_ASSERT(width >= 0.0);
}

cwPenSegment::cwPenSegment(const cwPenSegment &rhs) : d(rhs.d)
{
}

cwPenSegment &cwPenSegment::operator=(const cwPenSegment &rhs)
{
    if (this != &rhs)
        d.operator=(rhs.d);
    return *this;
}

cwPenSegment::~cwPenSegment()
{
}

/**
 * @brief cwPenSegment::isNull
 * @return Return true if created with the default constructer, otherwise returns false
 */
bool cwPenSegment::isNull() const
{
    return d->Width < 0.0;
}

/**
 * @brief cwPenSegment::p1
 * @return Returns the first point in the pen segment
 */
QPointF cwPenSegment::point() const
{
    return d->Point;
}

/**
 * @brief cwPenSegment::width
 * @return Return's the pen segment's width
 */
double cwPenSegment::width() const
{
    return d->Width;
}
