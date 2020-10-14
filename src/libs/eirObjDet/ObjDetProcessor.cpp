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
    finder()->initialize();
}

void ObjDetProcessor::initialize()
{
    TRACEQFI << cvClassifier::typeName(cmType)();
    classifierPool->r(cmType).initialize();
    reset();
}

void ObjDetProcessor::reset()
{
    TRACEQFI << cvClassifier::typeName(cmType)();
    mError.clear();
    mInputImage.nullify();
    mGreyInputMat.clear();
    mMethodString.clear();
    mRectList.clear();
    mResultList.clear();
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
    XerReturn<QQRectList> rtnerr;
    TRACE << mGreyInputMat.toDebugString();

    rtnerr = finder()->findRectangles(mGreyInputMat, showMat, region);
    mMethodString = finder()->methodString();
    return rtnerr;
}

int ObjDetProcessor::groupRects()
{
    TRACEFN; MUSTDO(it);
    return INT_MIN;
}
