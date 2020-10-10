#pragma once
#include "eirObjDet.h"

#include <QSharedDataPointer>
#include <eirType/DProperty.h>

#include <QTransform>

#include <eirBase/Uuid.h>
#include <eirQtCV/cvCascade.h>
#include <eirType/MultiName.h>
#include <eirType/QQSize.h>
#include <eirType/QQString.h>

#define CATEGORYENTRY_DATAPROPS(TND) \
    TND(cvCascadeType, CascadeType, cvCascadeType::nullType) \
    TND(bool, IsDefault, false) \
    TND(int, Version, 0) \
    TND(MultiName, Name, MultiName()) \
    TND(QQString, Description, QQString()) \
    TND(QQString, XmlFileName, QQString()) \
    TND(QQSize, CoreSize, QQSize()) \
    TND(QTransform, TightFaceTransform, QTransform()) \
    TND(QTransform, FullFaceTransform, QTransform()) \

class RectFinderCatalogEntryData : public QSharedData
{
    DECLARE_CHILD_DATAPROPS(CATEGORYENTRY_DATAPROPS)
public:
    RectFinderCatalogEntryData(void)
    {
        DEFINE_DATAPROPS_CTORS(CATEGORYENTRY_DATAPROPS)
    }
};

class EIROBJDET_EXPORT RectFinderCatalogEntry
{
    DECLARE_PARENT_DATAPROPS(CATEGORYENTRY_DATAPROPS)
    DECLARE_DATAPROPS(RectFinderCatalogEntry, RectFinderCatalogEntryData)
public:
    Uuid uid() const;

private:
    const Uuid mUid;
};

