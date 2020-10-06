#include "ObjDetProcessor.h"

#include <eirXfr/Debug.h>

ObjDetProcessor::ObjDetProcessor(const cvCascade::Type cascadeType)
    : cmType(cascadeType) , mpCascade(new cvCascade(cmType)) {;}


cvCascade *ObjDetProcessor::cascade()
{
    TSTALLOC(mpCascade);
    return mpCascade;
}

void ObjDetProcessor::configure(const Settings::Key key)
{
    TRACEQFI << key();
    mRectSettings.read(key + "/RectFinder");
    mGroupSettings.read(key + "/RectGrouper");
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
    EXPECTNOT(mGreyInputMat.isNull());
    BEXPECTEQ(1, mGreyInputMat.depthInBytes());
}

int ObjDetProcessor::findRects(
        #ifdef QTCV_SETTINGS_HACK
            const unsigned mScaleFactor,
            const signed mNeighbors,
            const unsigned mMinQuality,
        #endif
        const bool showMat, const QQRect &region)
{
    TRACEFN; TOUSE(region);
    TRACE << mGreyInputMat.toDebugString();
    mRectList.clear();
    int rectCount = cascade()->detectRectangles(mRectSettings.toMap(),
                                            #ifdef QTCV_SETTINGS_HACK
                                                  mScaleFactor,
                                                  mNeighbors,
                                                  mMinQuality,
                                            #endif
                                                mGreyInputMat, showMat, region);
    mRectList = cascade()->rectList();
    return rectCount;
}

int ObjDetProcessor::groupRects()
{
    TRACEFN; MUSTDO(it);
    return INT_MIN;
}
