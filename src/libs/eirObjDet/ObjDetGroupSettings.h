#pragma once
#include "eirObjDet.h"

#include <QSharedDataPointer>

#include <eirExe/Settings.h>

class ObjDetGroupSettingsData;

class EIROBJDET_EXPORT ObjDetGroupSettings
{
public:
    ObjDetGroupSettings();
    ObjDetGroupSettings(const ObjDetGroupSettings &);
    ObjDetGroupSettings &operator=(const ObjDetGroupSettings &);
    ~ObjDetGroupSettings();

    unsigned minQuality() const;

    void read(const Settings::Key groupKey);
    QSettings::SettingsMap toMap(const Settings::Key groupKey=Settings::Key()) const;
    void dump(const Settings::Key groupKey=Settings::Key()) const;

private:
    QSharedDataPointer<ObjDetGroupSettingsData> data;
};

