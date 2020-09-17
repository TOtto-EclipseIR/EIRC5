#pragma once
#include "eirImage.h"

#include <eirType/QQImage.h>
#include <eirType/QQRectList.h>
#include <eirExe/Configuration.h>
#include <eirObjDet/ObjDetPak.h>
#include <eirObjDet/ObjDetResultList.h>

#include "ColorWheel.h"

class EIRIMAGE_EXPORT SimpleRectMarker : public QQImage
{
public:
    SimpleRectMarker(const QQImage &inputImage);
    void markAll(const Configuration &markRectConfig,
                 const QQRectList &rectList);
    void mark(const Configuration &markRectConfig,
              const ObjDetResultList &resultList,
              const ColorWheel &wheel,
              const bool markAll=false);
    ColorWheel qualityWheel();

private:
    ColorWheel mQualityWheel;
};

