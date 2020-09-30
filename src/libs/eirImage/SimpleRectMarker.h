#pragma once
#include "eirImage.h"

#include <eirExe/Settings.h>
#include <eirType/QQImage.h>
#include <eirType/QQRectList.h>
#include <eirObjDet/ObjDetResultList.h>

#include "ColorWheel.h"

class EIRIMAGE_EXPORT SimpleRectMarker : public QQImage
{
public:
    SimpleRectMarker(const QQImage &inputImage);
    void markAll(const Settings::Key &groupKey,
                 const QQRectList &rectList);
    void mark(const Settings::Key &groupKey,
              const ObjDetResultList &resultList,
              const ColorWheel &wheel,
              const bool markAll=false);
    ColorWheel qualityWheel();

private:
    ColorWheel mQualityWheel;
};

