/**************************************************************************
**
**    Copyright (C) 2014 by Philip Schuchardt
**    www.cavewhere.com
**
**************************************************************************/


#ifndef CWSKETCHVIEW_H
#define CWSKETCHVIEW_H

//Qt includes
#include <QObject>
#include <QPointer>
#include <QGraphicsScene>
#include <QModelIndex>

//Our includes
class cwSketchModel;
class cwPenStrokeItem;

class cwSketchView : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QGraphicsScene* scene READ scene WRITE setScene NOTIFY sceneChanged)
    Q_PROPERTY(cwSketchModel* sketchModel READ sketchModel WRITE setSketchModel NOTIFY sketchModelChanged)

public:
    explicit cwSketchView(QObject *parent = 0);

    QGraphicsScene* scene() const;
    void setScene(QGraphicsScene* scene);

    cwSketchModel* sketchModel() const;
    void setSketchModel(cwSketchModel* sketchModel);

signals:
    void sceneChanged();
    void sketchModelChanged();

private slots:
    void insertStrokes(const QModelIndex & parent, int first, int last);
    void updateAllStrokeItems();
    void updateStrokeData(QModelIndex topLeft, QModelIndex bottomRight);

private:
    QPointer<QGraphicsScene> Scene; //!<
    QPointer<cwSketchModel> SketchModel; //!<
    QList<cwPenStrokeItem*> StrokeItems;

    void updateStrokeItemAt(int index);
    void resizeStrokeItems();
};

#endif // CWSKETCHVIEW_H
