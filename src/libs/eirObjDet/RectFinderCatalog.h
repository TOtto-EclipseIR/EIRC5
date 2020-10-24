#pragma once
#include "eirObjDet.h"

#include <QMap>
#include <QPair>

#include <eirBase/Uuid.h>
#include <eirQtCV/cvClassifier.h>
#include <eirType/DualMap.h>
#include <eirType/QQFileInfo.h>
#include <eirXfr/XerEntry.h>

#include "RectFinderCatalogEntry.h"

class EIROBJDET_EXPORT RectFinderCatalog
{
public:
    class CascadeName
    {
        CascadeName();
        CascadeName(const cvClassifier::Type type, const MultiName &name);
        void set(const cvClassifier::Type type, const MultiName &name);
        void setType(const cvClassifier::Type type);
        void setName(const MultiName &name);

        cvClassifier::Type type() const;
        MultiName name() const;

    private:
        QPair<cvClassifier::Type, MultiName> mCascadeName;
    };

public:
    RectFinderCatalog();
    void addCatalog(const QQFileInfo &catalogFileInfo);
    void addEntry(const RectFinderCatalogEntry entry);
    void addEntry(const Settings::Key entryKey);
    XerEntry writeCatalog(const QQFileInfo &catalogFileInfo);

    Uuid::List typeEntries(const cvClassifier::Type type) const;
    Uuid defaultCascade(const cvClassifier::Type type) const;
    MultiName cascadeName(const Uuid id) const;
    RectFinderCatalogEntry entry(const Uuid uid) const;

private:
    QMap<cvClassifier::Type, Uuid> mTypeUidDefaultMap;
    QMap<Uuid, RectFinderCatalogEntry> mUidEntryMap;
    DualMap<Uuid, CascadeName> mUidCascadeNameDMap;
};

