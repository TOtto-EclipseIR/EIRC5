#include "ObjDetProcessor.h"

#include <eirXfr/Debug.h>

ObjDetProcessor::ObjDetProcessor(const cvCascade::Type cascadeType)
    : cmType(cascadeType) , mpCascade(new cvCascade(cmType)) {;}


cvCascade *ObjDetProcessor::cascade()
{
    TSTALLOC(mpCascade);
    return mpCascade;
}

void ObjDetProcessor::configure(const Settings::Key rectKey, const Settings::Key groupKey)
{
    TRACEQFI << rectKey() << groupKey();
    mRectSettings.read(rectKey);
    mGroupSettings.read(groupKey);
}

void ObjDetProcessor::setImage(const QQImage &inputImage)
{
    TRACEQFI << inputImage;
    mInputImage = inputImage.convertToFormat(QImage::Format_ARGB32);
    mGreyInputMat.setGrey(mInputImage);
}

int ObjDetProcessor::findRects(const QQRect &region)
{
    TRACEFN; MUSTDO(it); TOUSE(region);
    return INT_MIN;
}

int ObjDetProcessor::groupRects()
{
    TRACEFN; MUSTDO(it);
    return INT_MIN;
}
