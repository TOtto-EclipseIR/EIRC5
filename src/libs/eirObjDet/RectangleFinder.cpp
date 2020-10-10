#include "RectangleFinder.h"

#include <eirXfr/Debug.h>

RectangleFinder::RectangleFinder(const cvCascade::Type cascadeType, const Settings::Key finderKey, QObject *parent)
    : QObject(parent)
    , cmType(cascadeType)
    , cmFinderKey(finderKey)
    , cmCascade(cascadeType)
{
    TRACEQFI << cvCascade::typeName(cascadeType)() << finderKey() << QOBJNAME(parent);
    setObjectName("RectangleFinder:"+cvCascade::typeName(cascadeType));
    CONNECT(this, &RectangleFinder::ctord,
            this, &RectangleFinder::initialize);
    MUSTDO(it);
    EMIT(ctord());
}

void RectangleFinder::initialize()
{
    TRACEQFI << QOBJNAME(parent());

    MUSTDO(it);
    EMIT(initialized());
}

void RectangleFinder::setCascadeBaseDir()
{
    TRACEQFI << QOBJNAME(parent());

    MUSTDO(it);
    EMIT(baseDirSet(cmType, QQDir()));
}

void RectangleFinder::loadCascade(const QString &cascadeXmlFileName)
{
    MUSTUSE(cascadeXmlFileName);
}

void RectangleFinder::findRectangles(const cvMat greyMat, const bool showDetect, const QQRect &region)
{
    TRACEQFI << greyMat.toDebugString() << showDetect << region;
    cmCascade.detectRectangles(greyMat, mParameters, showDetect, region);
    MUSTDO(calculateParameters);
}

