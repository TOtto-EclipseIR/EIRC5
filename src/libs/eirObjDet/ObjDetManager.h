#pragma once
#include "eirObjDet.h"

#include <QObject>

class EIROBJDET_EXPORT ObjDetManager : public QObject
{
    Q_OBJECT
public:
    explicit ObjDetManager(QObject *parent = nullptr);

signals:

};

