#pragma once
#include "eirObjDet.h"

#include <QObject>

class EIROBJDET_EXPORT RectangleGrouper : public QObject
{
    Q_OBJECT
public:
    explicit RectangleGrouper(QObject *parent = nullptr);

signals:

};

