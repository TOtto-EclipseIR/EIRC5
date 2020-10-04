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
    int mMinAcross=0;
    int mMaxAcross=0;
    int mMaxDetectors=0;
    int mScaleFactor=0;
    int mNeighbors=0;
    QQSize mMinSize;
    QQSize mMaxSize;

};

ObjDetRectSettings::ObjDetRectSettings() : data(new ObjDetRectSettingsData) {;}
ObjDetRectSettings::ObjDetRectSettings(const ObjDetRectSettings &rhs) : data(rhs.data) {;}
ObjDetRectSettings::~ObjDetRectSettings() {;}

void ObjDetRectSettings::read(const Settings::Key rectKey)
{
    STG->beginGroup(rectKey);
    data->mMinAcross        = STG->unsignedInt("MinAcross");
    data->mMaxAcross        = STG->unsignedInt("MaxAcross");
    data->mScaleFactor      = STG->unsignedInt("ScaleFactor");
    data->mNeighbors        = STG->unsignedInt("Neighbors");
    data->mMaxDetectors     = STG->unsignedInt("MaxDetectors");
    data->mMinSize.set(STG->string("MinSize"));
    data->mMaxSize.set(STG->string("MaxSize"));
    STG->endGroup();
}

ObjDetRectSettings &ObjDetRectSettings::operator=(const ObjDetRectSettings &rhs)
{
    if (this != &rhs) data.operator=(rhs.data);
    return *this;
}

