#include "ObjDetProcessor.h"

#include <APP>
#include <eirXfr/Debug.h>

ObjDetProcessor::ObjDetProcessor(const cvClassifier::Type cascadeType, const Settings::Key objDetKey, QObject * parent)
    : QObject(parent)
    , cmType(cascadeType)
    , cmResourceKey(objDetKey+"Resources")
    , cmObjDetTypeKey(objDetKey+cvClassifier::typeName(cascadeType))
    , mpRectFinder(new RectangleFinder(cmType, objDetKey+"Resources/RectFinder",
                                       cmObjDetTypeKey+"RectFinder", parent))
    , mpRectGrouper(new RectangleGrouper(cmType, cmObjDetTypeKey+"RectGrouper", parent))
{
    TRACEQFI << cvClassifier::typeName(cmType)() << cmObjDetTypeKey() << QOBJNAME(parent);
    setObjectName("ObjDetProcessor");
    MUSTDO(more);
}

void ObjDetProcessor::setImage(const QQImage &inputImage)
{
    TRACEQFI << inputImage;
    mInputImage = inputImage.convertToFormat(QImage::Format_ARGB32);
    mGreyInputMat = cvMat::greyFromImage(mInputImage);
    EXPECTNOT(mGreyInputMat.isNull());
    BEXPECTEQ(1, mGreyInputMat.depthInBytes());
}

XerReturn<QQRectList> ObjDetProcessor::findRects(const bool showMat, const QQRect &region)
{
    TRACEQFI << showMat << region;
    TOUSE(region);
    TRACE << mGreyInputMat.toDebugString();
    return finder()->findRectangles(mGreyInputMat, showMat, region);
}

int ObjDetProcessor::groupRects()
{
    TRACEFN; MUSTDO(it);
    return INT_MIN;
}
