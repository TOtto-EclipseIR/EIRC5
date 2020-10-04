#pragma once
#include "eirObjDet.h"

#include <eirExe/Settings.h>
#include <eirQtCV/cvCascade.h>
#include <eirType/QQImage.h>
#include <eirType/QQRectList.h>

#include "ObjDetResultList.h"
#include "ObjDetGroupSettings.h"
#include "ObjDetRectSettings.h"

class EIROBJDET_EXPORT ObjDetProcessor
{
public:
    ObjDetProcessor(const cvCascadeType cascadeType);
    void configure(const Settings::Key rectKey, const Settings::Key groupKey);
    void setImage(const QQImage &inputImage);
    QQRectList findRects();
    ObjDetResultList groupRects(const QQRectList &rectList);

private:
    const cvCascadeType cmType=cvCascadeType::nullType;
    cvCascade const * cmpCascade=nullptr;
    ObjDetRectSettings mRectSettings;
    ObjDetGroupSettings mGroupSettings;
};

