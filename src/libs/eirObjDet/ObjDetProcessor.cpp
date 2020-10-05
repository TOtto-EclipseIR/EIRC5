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
    mGreyInputMat = cvMat::greyFromImage(mInputImage);
    BEXPECTNOT(mGreyInputMat.isNull());
    BEXPECTEQ(1, mGreyInputMat.depthInBytes());
}

int ObjDetProcessor::findRects(const bool showMat, const QQRect &region)
{
    TRACEFN; TOUSE(region);
    TRACE << mGreyInputMat.toDebugString();
    mRectList.clear();
    int rectCount = cascade()->detectRectangles(mRectSettings.toMap(), mGreyInputMat, showMat, region);
    mRectList = cascade()->rectList();
    return rectCount;
}

int ObjDetProcessor::groupRects()
{
    TRACEFN; MUSTDO(it);
    return INT_MIN;
}
