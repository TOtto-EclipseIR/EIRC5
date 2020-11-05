#pragma once
#include "eirImage.h"

#include <eirType/Enumeration.h>

#define MARKERTYPE_ENUM(NV) \
    NV(Null, = 0)  \
    NV(AcquisitionBase, = 10)   \
    NV(Original, )   \
    NV(FrameBase, = 20)   \
    NV(PreScanRect, )   \
    NV(PreScanAllRect, )   \
    NV(FaceBase, = 100)   \



class EIRIMAGE_EXPORT MarkerType : public Enumeration
{
    DECLARE_ENUMERATION(MarkerType, MARKERTYPE_ENUM)
};

