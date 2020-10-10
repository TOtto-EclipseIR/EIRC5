#pragma once
#include "eirObjDet.h"

#include <QObject>

#include <eirExe/Settings.h>
#include <eirQtCV/cvCascade.h>

class EIROBJDET_EXPORT RectangleGrouper : public QObject
{
    Q_OBJECT
public:
    explicit RectangleGrouper(const cvCascade::Type cascadeType, const Settings::Key grouperKey, QObject *parent = nullptr);

signals:

private:
    cvCascadeType cmType;
    Settings::Key cmGrouperKey;

};

