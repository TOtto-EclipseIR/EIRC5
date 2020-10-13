#include "RectangleFinder.h"

#include <eirQtCV/cvClassifierPool.h>
#include <eirXfr/Debug.h>


RectangleFinder::RectangleFinder(QObject *parent)
    : QObject(parent)
    , cmType(cvClassifier::nullType)
{
    TRACEQFI << "null" << QOBJNAME(parent);
    setObjectName("RectangleFinder:"+cvClassifier::typeName(cvClassifier::nullType));
}

RectangleFinder::RectangleFinder(const cvClassifier::Type cascadeType, const Settings::Key finderKey, QObject *parent)
    : QObject(parent)
    , cmType(cascadeType)
    , cmFinderKey(finderKey)
{
    TRACEQFI << cvClassifier::typeName(cascadeType)() << finderKey() << QOBJNAME(parent);
    setObjectName("RectangleFinder:"+cvClassifier::typeName(cascadeType));
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

void RectangleFinder::readCatalogs()
{
    TRACEQFI << QOBJNAME(parent());

    MUSTDO(it);
    EMIT(catalogsRead());
}

void RectangleFinder::loadCascade(const QString &cascadeXmlFileName)
{
    MUSTUSE(cascadeXmlFileName);
}

void RectangleFinder::findRectangles(const cvMat greyMat, const bool showDetect, const QQRect &region)
{
    TRACEQFI << greyMat.toDebugString() << showDetect << region;
    classifierPool->r(cmType).detectRectangles(greyMat, mParameters, showDetect, region);
    MUSTDO(calculateParameters);
}

