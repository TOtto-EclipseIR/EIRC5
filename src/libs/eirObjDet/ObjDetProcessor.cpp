#include "ObjDetProcessor.h"

#include <eirXfr/Debug.h>

ObjDetProcessor::ObjDetProcessor(const cvClassifier::Type cascadeType, const Settings::Key objDetKey, QObject * parent)
    : QObject(parent)
    , cmType(cascadeType)
    , cmObjDetTypeKey(objDetKey+cvClassifier::typeName(cascadeType))
    , mpRectFinder(new RectangleFinder(cmType, cmObjDetTypeKey+"RectFinder", parent))
    , mpRectGrouper(new RectangleGrouper(cmType, cmObjDetTypeKey+"RectGrouper", parent))
{
    TRACEQFI << cvClassifier::typeName(cmType)() << cmObjDetTypeKey() << QOBJNAME(parent);
    setObjectName("ObjDetProcessor");
    MUSTDO(more);
}

RectangleFinder *ObjDetProcessor::finder()
{
    return mpRectFinder;
}

RectangleGrouper *ObjDetProcessor::grouper()
{
    return mpRectGrouper;
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
    finder()->findRectangles(mGreyInputMat, showMat, region);
    return mRectList.count();
}

int ObjDetProcessor::groupRects()
{
    TRACEFN; MUSTDO(it);
    return INT_MIN;
}
