#include "ObjDetProcessor.h"

#include <APP>
#include <eirXfr/Debug.h>

ObjDetProcessor::ObjDetProcessor(const cvClassifier::Type cascadeType,
                                 const Settings::Key objDetKey,
                                 QObject * parent)
    : QObject(parent)
    , cmType(cascadeType)
    , mResourceKey(objDetKey.appended("Resources"))
    , mObjDetTypeKey(objDetKey.appended(cvClassifier::typeName(cascadeType)()))
    , mpRectFinder(new RectangleFinder(cmType,
                        mResourceKey.appended("RectFinder"),
                        mObjDetTypeKey.appended("RectFinder"), parent))
    , mpRectGrouper(new RectangleGrouper(cmType,
                        mObjDetTypeKey.appended("RectGrouper"), parent))
{
    TRACEQFI << cvClassifier::typeName(cmType)() << mResourceKey()
             << mObjDetTypeKey() << QOBJNAME(parent);
    setObjectName("ObjDetProcessor");
}

void ObjDetProcessor::initialize()
{
    TRACEQFI << cvClassifier::typeName(cmType)() << QOBJNAME(this);
    CONNECT(this, &ObjDetProcessor::setupFinished,
            finder(), &RectangleFinder::initialize);
    CONNECT(this, &ObjDetProcessor::setupFinished,
            grouper(), &RectangleGrouper::initialize);
    reset();
    EMIT(setupFinished());
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
    EMIT(resetd());
}

void ObjDetProcessor::setImage(const QQImage &inputImage)
{
    TRACEQFI << inputImage;
    mInputImage = inputImage.convertToFormat(QImage::Format_ARGB32);
    mGreyInputMat = cvMat::greyFromImage(mInputImage);
    EXPECTNOT(mGreyInputMat.isNull());
    BEXPECTEQ(1, mGreyInputMat.depthInBytes());
}

XerReturn<QQRectList> ObjDetProcessor::findRects(const bool showMat,
                                                 const QQRect &region)
{
    TRACEQFI << showMat << region;
    TOUSE(region);
    XerReturn<QQRectList> rtnerr;
    TRACE << mGreyInputMat.toDebugString();

    rtnerr = finder()->findRectangles(mGreyInputMat, showMat, region);
    mMethodString = finder()->methodString();
    DUMP << rtnerr.toDebugString();
    return rtnerr;
}

int ObjDetProcessor::groupRects()
{
    TRACEFN; MUSTDO(it);
    return INT_MIN;
}
