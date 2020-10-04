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

    void read(const Settings::Key groupKey);

private:
    QSharedDataPointer<ObjDetGroupSettingsData> data;
};

