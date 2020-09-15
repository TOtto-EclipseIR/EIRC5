#pragma once

#include <eirType/Enumeration.h>

#define MARKEDFRAME_ENUM(NV) \
    NV(nullFrame, = 0)  \
    NV(Capture, ) \
    NV(Rectangle, ) \
    NV(sizeFrame, ) \
    NV(nullCropped, = 100)      /* Start Faces */ \
    NV(RectangleFace, )         /* (croppedd first) */ \
    NV(EyesRectangles, ) \
    NV(NoseRectangles, ) \
    NV(MouthRectangles, ) \
    NV(CropFace, ) \
    NV(NoEyesFace, ) \
    NV(BadEyesFace, ) \
    NV(maxCropped, )            /* End Cropped Faces */ \
    NV(nullNormalized, = 110)   /* Start Normalozed Faces*/ \
    NV(NormalizedFace, ) \
    NV(MarkedFace, ) \
    NV(MatchedFace, )           /* Last Normalozed Faces*/ \
    NV(maxNormalized, )         /* End (all) Faces */ \

class MarkedFrame : public Enumeration
{
    DECLARE_ENUMERATION(MarkedFrame, MARKEDFRAME_ENUM);
};
