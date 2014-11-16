/**************************************************************************
**
**    Copyright (C) 2014 by Philip Schuchardt
**    www.cavewhere.com
**
**************************************************************************/


#include "cwSketchModel.h"

cwSketchModel::cwSketchModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

/**
 * @brief cwSketchModel::roleNames
 * @return
 */
QHash<int, QByteArray> cwSketchModel::roleNames() const
{
   QHash<int, QByteArray> roles;
   roles.insert(ColorRole, "colorRole");
   roles.insert(StrokeRole, "strokeRole");
   return roles;
}

/**
 * @brief cwSketchModel::data
 * @param index
 * @param role
 * @return
 */
QVariant cwSketchModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) {
        return QVariant();
    }

    const cwPenStroke& stroke = Strokes.at(index.row());

    switch(role) {
    case ColorRole:
        return stroke.color();
    case StrokeRole:
        return QVariant::fromValue(stroke);
    default:
        return QVariant();
    }
}

/**
 * @brief cwSketchModel::rowCount
 * @param parent
 * @return Returns the number of strokes in the sketch
 */
int cwSketchModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return Strokes.size();
}

/**
 * @brief cwSketchModel::addStroke
 * @param stroke
 *
 * This add a new stroke to the sketch
 */
void cwSketchModel::addStroke(const cwPenStroke &stroke)
{
    int numberStrokes = rowCount();
    beginInsertRows(QModelIndex(), numberStrokes, numberStrokes);
    Strokes.append(stroke);
    endInsertRows();
}

/**
 * @brief cwSketchModel::addToLastStroke
 * @param segment
 *
 * This will add a new segement to the end of the last stroke in the sketch.
 *
 * This will automatically reject any segment that has the same point as the current
 * last segment in the last stroke.
 */
void cwSketchModel::addToLastStroke(const cwPenSegment &segment)
{
    Q_ASSERT(rowCount() >= 1); //If this fails call addStroke

    QModelIndex lastIndex = index(rowCount() - 1);

    cwPenStroke& lastStroke = Strokes.last();
    int lastIndexOfStroke = lastStroke.numberOfSegments() - 1;
    if(lastIndexOfStroke >= 0) {
        cwPenSegment lastSegmentOfLastStroke = lastStroke.segment(lastIndexOfStroke);
        if(lastSegmentOfLastStroke.point() == segment.point()) {
            return;
        }
    }

    lastStroke.append(segment);
    emit dataChanged(lastIndex, lastIndex, QVector<int>() << StrokeRole);
}
