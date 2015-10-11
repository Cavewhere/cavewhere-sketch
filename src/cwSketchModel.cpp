/**************************************************************************
**
**    Copyright (C) 2014 by Philip Schuchardt
**    www.cavewhere.com
**
**************************************************************************/


#include "cwSketchModel.h"

cwSketchModel::cwSketchModel(QObject *parent) :
    QAbstractItemModel(parent)
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
   roles.insert(SegementRole, "segmentRole");
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

    int strokeIndex = -1;

    if(index.parent().isValid()) {
        strokeIndex = index.parent().row();
    } else {
        strokeIndex = index.row();
    }

    const cwPenStroke& stroke = Strokes.at(strokeIndex);

    switch(role) {
    case ColorRole:
        return stroke.color();
    case StrokeRole:
        return QVariant::fromValue(stroke);
    case SegementRole:
        //Returns a segement from the stroke
        return QVariant::fromValue(stroke.segment(index.row()));
    default:
        return QVariant();
    }
}

/**
 * @brief cwSketchModel::rowCount
 * @param parent
 * @return Returns the number of strokes in the sketch
 *
 * If the parent is valid, this returns the number of segementsn in the parent stroke
 */
int cwSketchModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid()) {
        const cwPenStroke& stroke = Strokes.at(parent.row());
        return stroke.numberOfSegments();
    }
    return Strokes.size();
}

/**
 * @brief cwSketchModel::parent
 * @param child
 * @return
 */
QModelIndex cwSketchModel::parent(const QModelIndex &child) const
{
    if((int)child.internalId() >= 0) {
        //The child is a segement, the child internal id is the stoke index
        return createIndex(child.internalId(), 0, -1);
    }
    //The child is a stroke, that has no parent
    return QModelIndex();
}

/**
 * @brief cwSketchModel::index
 * @param row
 * @param column
 * @param parent
 * @return
 */
QModelIndex cwSketchModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(column);
    if(parent.isValid()) {
        return createIndex(row, 0, parent.row());
    }
    return createIndex(row, 0, -1);
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

    beginInsertRows(lastIndex, lastStroke.numberOfSegments(), lastStroke.numberOfSegments());
    lastStroke.append(segment);
    endInsertRows();
//    emit dataChanged(lastIndex, lastIndex, QVector<int>() << StrokeRole);
}
