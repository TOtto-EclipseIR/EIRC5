#include "RectangleFinder.h"

#include <APP>
#include <eirExe/Settings.h>
#include <eirQtCV/cvClassifierPool.h>
#include <eirXfr/Debug.h>


RectangleFinder::RectangleFinder(QObject *parent)
    : QObject(parent)
    , cmType(cvClassifier::nullType)
{
    TRACEQFI << "null" << QOBJNAME(parent);
    setObjectName("RectangleFinder:"+cvClassifier::typeName(cvClassifier::nullType));
}

RectangleFinder::RectangleFinder(const cvClassifier::Type cascadeType,
                                 const Settings::Key resourceKey,
                                 const Settings::Key finderKey,
                                 QObject *parent)
    : QObject(parent)
    , cmType(cascadeType)
    , cmResourceKey(resourceKey)
    , cmFinderKey(finderKey)
{
    TRACEQFI << cvClassifier::typeName(cascadeType)() << finderKey() << QOBJNAME(parent);
    setObjectName("RectangleFinder:"+cvClassifier::typeName(cascadeType));
    EMIT(ctord(cmType));
}

cvClassifier::Parameters RectangleFinder::parameters() const
{
    return mParameters;
}

QQString RectangleFinder::methodString() const
{
    return parameters().methodString(classifierPool->
                                     r(cmType).cascadeFileInfo());
}

void RectangleFinder::initialize()
{
    TRACEQFI << QOBJNAME(parent());
    CONNECT(this, &RectangleFinder::initialized,
            this, &RectangleFinder::setDetectorsBaseDir);
    TODO(readCatalogs);
    CONNECT(this, &RectangleFinder::baseDirSetup,
            this, &RectangleFinder::loadCascade);
    CONNECT(this, &RectangleFinder::cascadeLoaded,
            this, &RectangleFinder::finishSetup);
    DUMP << Qt::endl << classifierPool->statusStrings().join("\r\n");
    EMIT(initialized(cmType));
}

void RectangleFinder::readCatalogs()
{
    TRACEQFI << QOBJNAME(parent());

    MUSTDO(it);
    EMIT(catalogsRead(cmType));
}

void RectangleFinder::setDetectorsBaseDir()
{
    TRACEQFI << QOBJNAME(parent());
    QQString baseDirName = STG->string(cmResourceKey+"BaseDir");
    mBaseDir = QQDir(baseDirName);
    EMIT(baseDirSetup());
    EMIT(baseDirSet(cmType, mBaseDir));
}

void RectangleFinder::loadCascade()
{
    TRACEQFI << QOBJNAME(parent());
    QQString xmlFileName = STG->string(cmResourceKey+cvClassifier::typeName(cmType)+"XmlFile");
    if ( ! xmlFileName.isEmpty())
        loadCascadeFile(xmlFileName);
    DUMP << Qt::endl << classifierPool->statusStrings().join('\n');
}

void RectangleFinder::finishSetup()
{
    TRACEQFI << QOBJNAME(parent());
    EMIT(setupFinished(cmType));
}

XerReturn<QQRectList> RectangleFinder::findRectangles(const cvMat greyMat, const bool showDetect, const QQRect &region)

{
    TRACEQFI << greyMat.toDebugString() << showDetect << region;
    XerReturn<QQRectList> rtnerr;
    configure();
    rtnerr = classifierPool->r(cmType).detectRectangles(greyMat, mParameters, showDetect, region);
    if (rtnerr.isError() || rtnerr.isNull()
            || cvClassifier::PreScan != cmType) return rtnerr;
    return rtnerr.set(preScanMergeRects(rtnerr.result()));
}

void RectangleFinder::loadCascadeFile(const QString &cascadeXmlFileName)
{
    TRACEQFI << cascadeXmlFileName;
    QQFileInfo xmlFileInfo(mBaseDir, cascadeXmlFileName);
    loadCascadeFile(xmlFileInfo);
}

void RectangleFinder::loadCascadeFile(const QQFileInfo &cascadeFileInfo)
{
    TRACEQFI << cascadeFileInfo;
    EXPECT(classifierPool->r(cmType).loadCascade(cascadeFileInfo));
}

void RectangleFinder::configure()
{
    TRACEFN;
    STG->beginGroup(cmFinderKey);
    unsigned quality = STG->unsignedInt("Quality", 500);
    qreal factor = STG->realPerMille("ScaleFactor", 0.0);
    signed neighbors = STG->signedInt("Neighbors", -1);
    STG->endGroup();

    if (quality)
    {
        factor = 1.120;
        neighbors = cvClassifier::Parameters
                ::neighborsForPreScanQuality(quality);
    }
    else
    {
        factor = qIsNull(factor) ? 1.120 : factor;
        neighbors = (neighbors < 0) ? 2 : neighbors;
    }
    mParameters.setFactor(factor);
    mParameters.setNeighbors(neighbors);
    NEEDDO(sizes);
}

QQRectList RectangleFinder::preScanMergeRects(const QQRectList &rawRects)
{
    TRACEQFI << rawRects;
    QQRectList remainingRects = rawRects;
    QQRectList resultRects;
    while ( ! remainingRects.isEmpty())
    {
        QQRect currentRect = remainingRects.takeFirst();
        foreach (QQRect priorRect, resultRects)
        {
            if (priorRect.contains(currentRect))
                break;
            if (currentRect.contains(priorRect))
                resultRects.removeAll(priorRect);
            resultRects << currentRect;
        }
    }
    return resultRects;
}

