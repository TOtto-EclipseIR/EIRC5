#pragma once
#include "eirObjDet.h"

#include <QSharedDataPointer>
#include <eirType/DProperty.h>

#include <QTransform>

#include <eirBase/Uuid.h>
#include <eirQtCV/cvClassifier.h>
#include <eirType/MultiName.h>
#include <eirType/QQSize.h>
#include <eirType/QQString.h>

typedef cvClassifier::Type classifierType;

#define CATALOGENTRY_DATAPROPS(TND) \
    TND(classifierType, CascadeType, classifierType::nullType) \
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
    DECLARE_CHILD_DATAPROPS(CATALOGENTRY_DATAPROPS)
public:
    RectFinderCatalogEntryData(void)
    {
        DEFINE_DATAPROPS_CTORS(CATALOGENTRY_DATAPROPS)
    }
};

class EIROBJDET_EXPORT RectFinderCatalogEntry
{
    DECLARE_PARENT_DATAPROPS(CATALOGENTRY_DATAPROPS)
    DECLARE_DATAPROPS(RectFinderCatalogEntry, RectFinderCatalogEntryData)
public:
    Uuid uid() const;

private:
    const Uuid mUid;
};

