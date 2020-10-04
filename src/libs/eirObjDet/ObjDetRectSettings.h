#pragma once
#include "eirObjDet.h"

#include <QSharedDataPointer>

#include <eirExe/Settings.h>

class ObjDetRectSettingsData;

class EIROBJDET_EXPORT ObjDetRectSettings
{
public:
    ObjDetRectSettings();
    ObjDetRectSettings(const ObjDetRectSettings &);
    ObjDetRectSettings &operator=(const ObjDetRectSettings &);
    ~ObjDetRectSettings();

    void read(const Settings::Key rectKey);
    QSettings::SettingsMap toMap(const Settings::Key rectKey=Settings::Key()) const;
    void dump(const Settings::Key rectKey=Settings::Key()) const;

private:
    QSharedDataPointer<ObjDetRectSettingsData> data;
};

