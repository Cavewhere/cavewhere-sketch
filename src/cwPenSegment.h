/**************************************************************************
**
**    Copyright (C) 2014 by Philip Schuchardt
**    www.cavewhere.com
**
**************************************************************************/


#ifndef CWPENSEGMENT_H
#define CWPENSEGMENT_H

#include <QSharedDataPointer>
#include <QPointF>

class cwPenSegmentData;

/**
 * @brief The cwPenSegment class
 *
 * The pen segment represents a single line bit. Multiple pen segments can make
 * up a cwPenStroke.
 */
class cwPenSegment
{
public:
    cwPenSegment();
    cwPenSegment(QPointF point, double width);
    cwPenSegment(const cwPenSegment &);
    cwPenSegment &operator=(const cwPenSegment &);
    ~cwPenSegment();

    bool isNull() const;
    QPointF point() const;
    double width() const;

private:
    QSharedDataPointer<cwPenSegmentData> d;
};

#endif // CWPENSEGMENT_H
