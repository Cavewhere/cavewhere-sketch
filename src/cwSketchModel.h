/**************************************************************************
**
**    Copyright (C) 2014 by Philip Schuchardt
**    www.cavewhere.com
**
**************************************************************************/


#ifndef CWSKETCHMODEL_H
#define CWSKETCHMODEL_H

//Qt includes
#include <QAbstractListModel>

//Our includes
#include "cwPenStroke.h"

class cwSketchModel : public QAbstractListModel
{
    Q_OBJECT

    Q_ENUMS(Roles)
public:

    enum Roles {
        ColorRole,
        StrokeRole
    };

    explicit cwSketchModel(QObject *parent = 0);

    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    void addStroke(const cwPenStroke& stroke);
    void addToLastStroke(const cwPenSegment& segment);

signals:

public slots:

private:
    QList<cwPenStroke> Strokes;

};

#endif // CWSKETCHMODEL_H
