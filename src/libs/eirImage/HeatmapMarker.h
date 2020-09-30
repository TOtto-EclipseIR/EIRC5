#pragma once
#include "eirImage.h"

#include <eirExe/Settings.h>
#include <eirObjDet/ObjDetResultList.h>
#include <eirType/QQImage.h>

class EIRIMAGE_EXPORT HeatmapMarker : public QQImage
{
public:
    HeatmapMarker(const QQImage &inputImage);
<<<<<<< HEAD
    void mark(const Settings::Key &markHeatGroupKey,
=======
    void mark(const Settings::Key &groupKey,
>>>>>>> c9081049be86ebf94694ac1f2bc2ffa3efd7435d
              const ObjDetResultList &resultList);
};

