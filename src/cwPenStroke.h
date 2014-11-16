/**************************************************************************
**
**    Copyright (C) 2014 by Philip Schuchardt
**    www.cavewhere.com
**
**************************************************************************/


#ifndef CWPENSTROKE_H
#define CWPENSTROKE_H

//Qt includes
#include <QSharedDataPointer>
#include <QColor>
#include <QVariant>

//Our includes
#include <cwPenSegment.h>

class cwPenStrokeData;

class cwPenStroke
{
public:
    cwPenStroke();
    cwPenStroke(const cwPenStroke &);
    cwPenStroke &operator=(const cwPenStroke &);
    ~cwPenStroke();

    void append(const cwPenSegment& segment);
    cwPenSegment segment(int index) const;
    int numberOfSegments() const;

    void setColor(QColor color);
    QColor color() const;

private:
    QSharedDataPointer<cwPenStrokeData> d;
};

Q_DECLARE_METATYPE(cwPenStroke)


#endif // CWPENSTROKE_H
