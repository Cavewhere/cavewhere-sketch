/**************************************************************************
**
**    Copyright (C) 2014 by Philip Schuchardt
**    www.cavewhere.com
**
**************************************************************************/

//Our includes
#include "cwPenStroke.h"

//Qt includes
#include <QSharedData>

class cwPenStrokeData : public QSharedData {
public:
    cwPenStrokeData() :
        Color(Qt::black) {}

    QList<cwPenSegment> Segments;
    QColor Color;
};

cwPenStroke::cwPenStroke() : d(new cwPenStrokeData)
{
}

cwPenStroke::cwPenStroke(const cwPenStroke &rhs) : d(rhs.d)
{
}

cwPenStroke &cwPenStroke::operator=(const cwPenStroke &rhs)
{
    if (this != &rhs)
        d.operator=(rhs.d);
    return *this;
}

cwPenStroke::~cwPenStroke()
{
}

/**
 * @brief cwPenStroke::append
 * @param segment
 *
 * This adds segment to the stroke
 */
void cwPenStroke::append(const cwPenSegment &segment)
{
    d->Segments.append(segment);
}

/**
 * @brief cwPenStroke::segment
 * @param index
 * @return Return's the pen segment at index
 */
cwPenSegment cwPenStroke::segment(int index) const
{
    Q_ASSERT(index >= 0);
    Q_ASSERT(index < d->Segments.size());
    return d->Segments.at(index);
}

/**
 * @brief cwPenStroke::numberOfSegments
 * @return Return's the number of segements
 */
int cwPenStroke::numberOfSegments() const
{
    return d->Segments.size();
}

/**
 * @brief cwPenStroke::setColor
 * @param color
 *
 * Sets the color of the pen stroke
 */
void cwPenStroke::setColor(QColor color)
{
    d->Color = color;
}

/**
 * @brief cwPenStroke::color
 * @return Returns the color fo th pen
 */
QColor cwPenStroke::color() const
{
    return d->Color;
}
