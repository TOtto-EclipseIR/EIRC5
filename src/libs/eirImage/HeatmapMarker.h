#pragma once
#include "eirImage.h"

#include <eirExe/Configuration.h>
#include <eirObjDet/ObjDetResultList.h>
#include <eirType/QQImage.h>

class EIRIMAGE_EXPORT HeatmapMarker : public QQImage
{
public:
    HeatmapMarker(const QQImage &inputImage);
    void mark(const Configuration &markRectConfig,
              const ObjDetResultList &resultList);
};

