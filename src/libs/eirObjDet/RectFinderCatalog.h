#pragma once
#include "eirObjDet.h"

#include <QMap>
#include <QPair>

#include <eirBase/Uuid.h>
#include <eirQtCV/cvCascade.h>
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
        CascadeName(const cvCascadeType type, const MultiName &name);
        void set(const cvCascadeType type, const MultiName &name);
        void setType(const cvCascadeType type);
        void setName(const MultiName &name);

        cvCascadeType type() const;
        MultiName name() const;

    private:
        QPair<cvCascadeType, MultiName> mCascadeName;
    };

public:
    RectFinderCatalog();
    void addCatalog(const QQFileInfo &catalogFileInfo);
    void addEntry(const RectFinderCatalogEntry entry);
    void addEntry(const Settings::Key entryKey);
    XerEntry writeCatalog(const QQFileInfo &catalogFileInfo);

    Uuid::List typeEntries(const cvCascadeType type) const;
    Uuid defaultCascade(const cvCascadeType type) const;
    MultiName cascadeName(const Uuid id) const;
    RectFinderCatalogEntry entry(const Uuid uid) const;

private:
    QMap<cvCascadeType, Uuid> mTypeUidDefaultMap;
    QMap<Uuid, RectFinderCatalogEntry> mUidEntryMap;
    DualMap<Uuid, CascadeName> mUidCascadeNameDMap;
};

