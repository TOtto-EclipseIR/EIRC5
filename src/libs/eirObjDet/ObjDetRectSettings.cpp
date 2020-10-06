#include "ObjDetRectSettings.h"

#include <APP>
#include <eirExe/Settings.h>
#include <eirType/QQSize.h>

class ObjDetRectSettingsData : public QSharedData
{
    friend class ObjDetRectSettings;
public:
    ObjDetRectSettingsData() {;}

private:
    void read(const Settings::Key groupKey);

private:

private:
    unsigned mMinAcross=0;
    unsigned mMaxAcross=0;
    unsigned mMaxDetectors=0;
    unsigned mScaleFactor=0;
    signed mNeighbors=0;
    QQSize mMinSize;
    QQSize mMaxSize;

};

ObjDetRectSettings::ObjDetRectSettings() : data(new ObjDetRectSettingsData) {;}
ObjDetRectSettings::ObjDetRectSettings(const ObjDetRectSettings &rhs) : data(rhs.data) {;}
ObjDetRectSettings::~ObjDetRectSettings() {;}

signed ObjDetRectSettings::neighbors() const
{
    return data->mNeighbors;
}

unsigned ObjDetRectSettings::scaleFactor() const
{
    return data->mScaleFactor;
}

void ObjDetRectSettings::read(const Settings::Key rectKey)
{
    STG->beginGroup(rectKey);
    data->mMinAcross        = STG->unsignedInt("MinAcross");
    data->mMaxAcross        = STG->unsignedInt("MaxAcross");
    data->mScaleFactor      = STG->unsignedInt("ScaleFactor");
    data->mNeighbors        = STG->signedInt("Neighbors");
    data->mMaxDetectors     = STG->unsignedInt("MaxDetectors");
    data->mMinSize.set(STG->string("MinSize"));
    data->mMaxSize.set(STG->string("MaxSize"));
    STG->endGroup();
}

QSettings::SettingsMap ObjDetRectSettings::toMap(const Settings::Key rectKey) const
{
    QSettings::SettingsMap resultMap;
    if (rectKey.notEmpty()) STG->beginGroup(rectKey);
    resultMap.insert("MinAcross", STG->value("MinAcross"));
    resultMap.insert("MaxAcross", STG->value("MaxAcross"));
    resultMap.insert("ScaleFactor", STG->value("ScaleFactor"));
    resultMap.insert("Neighbors", STG->value("Neighbors"));
    resultMap.insert("MaxDetectors", STG->value("MaxDetectors"));
    resultMap.insert("MinSize", STG->value("MinSize"));
    resultMap.insert("MaxSize", STG->value("MaxSize"));
    if (rectKey.notEmpty()) STG->endGroup();
    return resultMap;
}

void ObjDetRectSettings::dump(const Settings::Key rectKey) const
{
    Settings::dump(toMap(rectKey));
}

ObjDetRectSettings &ObjDetRectSettings::operator=(const ObjDetRectSettings &rhs)
{
    if (this != &rhs) data.operator=(rhs.data);
    return *this;
}

