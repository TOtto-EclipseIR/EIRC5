#include "ObjDetGroupSettings.h"

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

ObjDetGroupSettings &ObjDetGroupSettings::operator=(const ObjDetGroupSettings &rhs)
{
    if (this != &rhs) data.operator=(rhs.data);
    return *this;
}

