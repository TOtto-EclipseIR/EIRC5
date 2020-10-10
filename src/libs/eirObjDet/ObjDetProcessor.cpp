#include "ObjDetProcessor.h"

#include <eirXfr/Debug.h>

ObjDetProcessor::ObjDetProcessor(const cvCascade::Type cascadeType, const Settings::Key objDetKey, QObject * parent)
    : QObject(parent)
    , cmType(cascadeType)
    , cmObjDetKey(objDetKey)
    , cmpRectFinder(new RectangleFinder(cmType, cmObjDetKey+"RectFinder", parent))
    , cmpRectGrouper(new RectangleGrouper(cmType, cmObjDetKey+"RectGrouper", parent))
{
    TRACEQFI << cvCascade::typeName(cmType)() << cmObjDetKey() << QOBJNAME(parent);
    setObjectName("ObjDetProcessor");
    MUSTDO(more);
}

void ObjDetProcessor::configure(const Settings::Key rectKey, const Settings::Key groupKey)
{
    TRACEQFI << rectKey() << groupKey();
    mRectKey = rectKey, mGroupKey = groupKey;
}

void ObjDetProcessor::setImage(const QQImage &inputImage)
{
    TRACEQFI << inputImage;
    mInputImage = inputImage.convertToFormat(QImage::Format_ARGB32);
    mGreyInputMat = cvMat::greyFromImage(mInputImage);
    EXPECTNOT(mGreyInputMat.isNull());
    BEXPECTEQ(1, mGreyInputMat.depthInBytes());
}

int ObjDetProcessor::findRects(const bool showMat, const QQRect &region)
{
    TRACEFN; TOUSE(region);
    TRACE << mGreyInputMat.toDebugString();
    mRectList.clear();
    int rectCount = cascade()->detectRectangles(mGreyInputMat, mRectKey, showMat, region);
    mRectList = cascade()->rectList();
    return rectCount;
}

int ObjDetProcessor::groupRects()
{
    TRACEFN; MUSTDO(it);
    return INT_MIN;
}
