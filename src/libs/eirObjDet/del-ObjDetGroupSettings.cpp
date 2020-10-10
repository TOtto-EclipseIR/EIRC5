#include "del-ObjDetGroupSettings.h"

#include <QString>

#include <APP>
#include <eirExe/Settings.h>
#include <eirType/QQSize.h>


class ObjDetGroupSettingsData : public QSharedData
{
    friend class ObjDetGroupSettings;
public:
    ObjDetGroupSettingsData() {;}

private:
    void setDefaults();
    void read(const Settings::Key groupKey);

private:
    QString mMethod;
    unsigned mMinQuality=0;
    unsigned mMaxQuality=0;
    unsigned mMaxResults=0;
    qreal mMaxDistance=0;
    bool mForce=false;
    unsigned mUnionOverlap=0;
    unsigned mUnionOrphan=0;
};

ObjDetGroupSettings::ObjDetGroupSettings() : data(new ObjDetGroupSettingsData) {;}
ObjDetGroupSettings::ObjDetGroupSettings(const ObjDetGroupSettings &rhs) : data(rhs.data) {;}
ObjDetGroupSettings::~ObjDetGroupSettings() {;}

unsigned ObjDetGroupSettings::minQuality() const
{
    return data->mMinQuality;
}

void ObjDetGroupSettings::read(const Settings::Key groupKey)
{
    STG->beginGroup(groupKey);

    data->mMethod           = STG->string("Method");
    data->mMinQuality       = STG->unsignedInt("MinQuality", 500);
    data->mMaxQuality       = STG->unsignedInt("MaxQuality", 1000);
    data->mMaxResults       = STG->unsignedInt("MaxResults", 99);
    data->mMaxDistance      = STG->real("MaxDistance", -1.0);
    data->mForce            = STG->boolean("Force", false);
    data->mUnionOverlap     = STG->unsignedInt("UnionOverlap", 500);
    data->mUnionOrphan      = STG->unsignedInt("UnionOrphan", 1);
    STG->endGroup();

}

QSettings::SettingsMap ObjDetGroupSettings::toMap(const Settings::Key groupKey) const
{
    QSettings::SettingsMap resultMap;
    if (groupKey.notEmpty()) STG->beginGroup(groupKey);
    resultMap.insert("Method", STG->value("Method"));
    resultMap.insert("MinQuality", STG->value("MinQuality"));
    resultMap.insert("MaxQuality", STG->value("MaxQuality"));
    resultMap.insert("MaxResults", STG->value("MaxResults"));
    resultMap.insert("MaxDistance", STG->value("MaxDistance"));
    resultMap.insert("Force", STG->value("Force"));
    resultMap.insert("UnionOverlap", STG->value("UnionOverlap"));
    resultMap.insert("UnionOrphan", STG->value("UnionOrphan"));
    if (groupKey.notEmpty()) STG->endGroup();
    return resultMap;
}

void ObjDetGroupSettings::dump(const Settings::Key groupKey) const
{
    Settings::dump(toMap(groupKey));
}

ObjDetGroupSettings &ObjDetGroupSettings::operator=(const ObjDetGroupSettings &rhs)
{
    if (this != &rhs) data.operator=(rhs.data);
    return *this;
}

