/**************************************************************************
**
**    Copyright (C) 2014 by Philip Schuchardt
**    www.cavewhere.com
**
**************************************************************************/

//Our includes
#include "cwSketchView.h"
#include "cwSketchModel.h"
#include "cwPenStrokeItem.h"
#include "cwPenSegment.h"

//Qt inludes
#include <QDebug>

cwSketchView::cwSketchView(QObject *parent) :
    QObject(parent)
{
}

/**
* @brief cwSketchView::scene
* @return Returns the graphics scene
*/
QGraphicsScene* cwSketchView::scene() const {
    return Scene.data();
}

/**
* @brief cwSketchView::setScene
* @param scene
*
* Sets the graphics scene that this view will add items to
*/
void cwSketchView::setScene(QGraphicsScene* scene) {
    if(Scene != scene) {
        Scene = scene;

        updateAllStrokeItems();

        emit sceneChanged();
    }
}

/**
* @brief cwSketchModel::sketchModel
* @return sketch model that's being view by the view
*/
cwSketchModel* cwSketchView::sketchModel() const {
    return SketchModel.data();
}

/**
* @brief cwSketchModel::setSketchModel
* @param sketchModel
*
* Sets the sketch model that this view will manage rendering objects
*/
void cwSketchView::setSketchModel(cwSketchModel* sketchModel) {
    if(SketchModel != sketchModel) {

        if(!SketchModel.isNull()) {
            disconnect(SketchModel.data(), &cwSketchModel::modelReset, this, &cwSketchView::updateAllStrokeItems);
            disconnect(SketchModel.data(), &cwSketchModel::rowsInserted, this, &cwSketchView::insertStrokes);
//            disconnect(SketchModel.data(), SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(updateStrokeData(QModelIndex,QModelIndex)));
        }

        SketchModel = sketchModel;

        if(!SketchModel.isNull()) {
            connect(SketchModel.data(), &cwSketchModel::modelReset, this, &cwSketchView::updateAllStrokeItems);
            connect(SketchModel.data(), &cwSketchModel::rowsInserted, this, &cwSketchView::insertStrokes);
//            connect(SketchModel.data(), SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(updateStrokeData(QModelIndex,QModelIndex)));
        }

        updateAllStrokeItems();

        emit sketchModelChanged();
    }
}

void cwSketchView::insertStrokes(const QModelIndex &parent, int first, int last)
{
//    Q_UNUSED(parent);

    if(SketchModel.isNull()) {
        return;
    }
    if(Scene.isNull()) {
        return;
    }

    if(parent.isValid()) {
        //Adding a segement
        cwPenStrokeItem* item = StrokeItems.at(parent.row());
        if(first == last && first == SketchModel->rowCount(parent) - 1) {
            QModelIndex index = SketchModel->index(first, -1, parent);
            item->appendSegement(index.data(cwSketchModel::SegementRole).value<cwPenSegment>());
        } else {
            qDebug() << "Segement appending is the only supported action";
        }

    } else {
        //Adding a Stroke
        resizeStrokeItems();

        for(int i = first; i <= last; ++i) {
            updateStrokeItemAt(i);
        }
    }
}

/**
 * @brief cwSketchView::updateAllStrokeItems
 *
 * This will update / add all stroke items in this view
 */
void cwSketchView::updateAllStrokeItems()
{
    if(Scene.isNull()) {
        return;
    }

    int numberOfStrokes = 0;
    if(!SketchModel.isNull()) {
        numberOfStrokes = SketchModel->rowCount();
    }

    insertStrokes(QModelIndex(), 0, numberOfStrokes-1);
}

/**
 * @brief cwSketchView::updateStrokeData
 * @param topLeft
 * @param bottomRight
 */
void cwSketchView::updateStrokeData(QModelIndex topLeft, QModelIndex bottomRight)
{
    for(int i = topLeft.row(); i <= bottomRight.row(); i++) {
        updateStrokeItemAt(i);
    }
}

/**
 * @brief cwSketchView::updateStrokeItemAt
 * @param index
 *
 * This will update the stroke item at index
 */
void cwSketchView::updateStrokeItemAt(int index)
{
    Q_ASSERT(index >= 0);
    Q_ASSERT(index < StrokeItems.size());

    cwPenStrokeItem* item = StrokeItems.at(index);

    QModelIndex modelIndex = SketchModel->index(index);
    cwPenStroke stroke = modelIndex.data(cwSketchModel::StrokeRole).value<cwPenStroke>();

    item->setPenStroke(stroke);
}

/**
 * @brief cwSketchView::resizeStrokeItems
 *
 * This will update the number of stroke items to equal number of strokes
 * in the sketch model.
 */
void cwSketchView::resizeStrokeItems()
{
    Q_ASSERT(!Scene.isNull());

    int numberOfStrokes = 0;
    if(!SketchModel.isNull()) {
        numberOfStrokes = SketchModel->rowCount();
    }

    if(numberOfStrokes == StrokeItems.size()) {
        return;
    }

    //Remove items
    for(int i = StrokeItems.size(); i > numberOfStrokes; i--) {
        cwPenStrokeItem* item = StrokeItems.last();
        delete item;
        StrokeItems.removeLast();
    }

    //Add new items
    for(int i = StrokeItems.size(); i < numberOfStrokes; i++) {
        cwPenStrokeItem* newItem = new cwPenStrokeItem();
        scene()->addItem(newItem);
        StrokeItems.append(newItem);
    }

    Q_ASSERT(StrokeItems.size() == numberOfStrokes);
}


