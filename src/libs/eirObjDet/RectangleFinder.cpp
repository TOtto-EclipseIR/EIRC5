#include "RectangleFinder.h"

#include <APP>
#include <eirExe/Settings.h>
#include <eirXfr/Debug.h>


RectangleFinder::RectangleFinder(QObject *parent)
    : QObject(parent)
    , cmType(cvClassifier::nullType)
{
    TRACEQFI << "null" << QOBJNAME(parent);
    setObjectName("RectangleFinder:"
            + cvClassifier::typeName(cvClassifier::nullType));
}

RectangleFinder::RectangleFinder(const cvClassifier::Type cascadeType,
                                 const Settings::Key resourceKey,
                                 const Settings::Key finderKey,
                                 QObject *parent)
    : QObject(parent)
    , cmType(cascadeType)
    , cmResourceKey(resourceKey)
    , cmResourceTypeKey(resourceKey.appended(cvClassifier::typeName(cmType)()))
    , cmFinderKey(finderKey)
{
    TRACEQFI << cvClassifier::typeName(cascadeType)()
             << cmResourceKey() << cmFinderKey() << QOBJNAME(parent);
    setObjectName("RectangleFinder:"+cvClassifier::typeName(cascadeType));
    EMIT(ctord(cmType));
}

cvClassifier::Parameters RectangleFinder::parameters() const
{
    return mParameters;
}

QQString RectangleFinder::methodString() const
{
    return parameters().methodString(gspClassifierPool->
                                     r(cmType).cascadeFileInfo());
}

void RectangleFinder::initialize()
{
    TRACEQFI << QOBJNAME(parent());
    CONNECT(this, &RectangleFinder::initialized,
            this, &RectangleFinder::setDetectorsBaseDir);
    CONNECT(this, &RectangleFinder::baseDirSetup,
            this, &RectangleFinder::loadCascade);
    CONNECT(this, &RectangleFinder::cascadeLoaded,
            this, &RectangleFinder::finishSetup);
    CONNECT(this, &RectangleFinder::cascadeNoLoad,
            this, &RectangleFinder::finishSetup);
    DUMP << Qt::endl << gspClassifierPool->statusStrings().join("\r\n");
    EMIT(initialized(cmType));
}

void RectangleFinder::setDetectorsBaseDir()
{
    TRACEQFI << QOBJNAME(parent());
    QQString baseDirName = STG->string(cmResourceKey.appended("BaseDir"));
    mBaseDir = QDir(baseDirName);
    EMIT(baseDirSetup());
    EMIT(baseDirSet(cmType, mBaseDir));
}

void RectangleFinder::loadCascade()
{
    TRACEQFI << QOBJNAME(parent());
    QQString xmlFileName = STG->string(cmResourceTypeKey.appended("XmlFile"));
    bool autoLoad = STG->boolean(cmResourceTypeKey.appended("AutoLoad"));
    if (autoLoad && ! xmlFileName.isEmpty())
    {
        loadCascadeFile(xmlFileName);
        EMIT(cascadeLoaded(cmType, mCascadeFileInfo));
    }
    else
    {
        EMIT(cascadeNoLoad(cmType));
    }
    DUMP << Qt::endl << gspClassifierPool->statusStrings().join('\n');
}

void RectangleFinder::finishSetup()
{
    TRACEQFI << QOBJNAME(parent());
    EMIT(setupFinished(cmType));
}

XerReturn<QQRectList> RectangleFinder::findRectangles(const cvMat greyMat,
                                                      const bool showDetect,
                                                      const QQRect &region)

{
    TRACEQFI << greyMat.toDebugString() << showDetect << region;
    XerReturn<QQRectList> rtnerr("RectangleFinder::findRectangles(rtnerr)");
    configure();
    rtnerr.set(gspClassifierPool->r(cmType)
            .detectRectangles(greyMat, mParameters, showDetect, region));
    EXPECTNOT(rtnerr.isNull());
    if (rtnerr.isError()) DUMP << rtnerr.toDebugString();
    if (rtnerr.isError()) return rtnerr;                        /* /========\ */
    QQRectList rectList = rtnerr.result();

    if (cvClassifier::PreScan == cmType && mParameters.preScanMerge())
        rectList = preScanMergeRects(rectList);
    return XerReturn<QQRectList>(rectList);
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
    EXPECT(gspClassifierPool->r(cmType).loadCascade(cascadeFileInfo));
    if (isLoaded()) mCascadeFileInfo = cascadeFileInfo;
}

void RectangleFinder::configure()
{
    TRACEQFI << cvClassifier::typeName(cmType)();
    if (cvClassifier::PreScan == cmType)
        return configurePreScan();
    MUSTDO(others);
}

void RectangleFinder::configurePreScan()
{
    TRACEQFI << cvClassifier::typeName(cmType)();
    STG->beginGroup(cmFinderKey);
    unsigned quality = STG->unsignedInt("PreScanQuality", 500);
    bool merge = STG->boolean("PreScanMerge", true);
    qreal factor = STG->realPerMille("ScaleFactor", 0);
    signed neighbors = STG->signedInt("Neighbors", -1);
    STG->endGroup();

    if (quality)
    {
        factor = 1.080;
        neighbors = cvClassifier::Parameters
                ::neighborsForPreScanQuality(quality);
    }
    else
    {
        factor = qIsNull(factor) ? 1.080 : factor;
        neighbors = (neighbors < 0) ? 2 : neighbors;
    }
    mParameters.setFactor(factor);
    mParameters.setNeighbors(neighbors);
    mParameters.setPreScanMerge(merge);
    NEEDDO(sizes);
}

QQRectList RectangleFinder::preScanMergeRects(const QQRectList &rawRects)
{
    TRACEQFI << rawRects;
#if 1
    return rawRects;
#else
    QQRectList remainingRects = rawRects;
    QQRectList resultRects;
    while ( ! remainingRects.isEmpty())
    {
        QQRect currentRect = remainingRects.takeFirst();
        DUMPVAL(currentRect);
        DUMPVAL(remainingRects);
        foreach (QQRect otherRect, remainingRects)
        {
            if (otherRect.contains(currentRect))
                break; // discard currentRect
            else if (currentRect.contains(otherRect))
                remainingRects.removeOne(otherRect);
            else
                resultRects << currentRect;
            DUMPVAL(resultRects.toDebugString());
        }
    }
    TRACERTN(resultRects);
    return resultRects;
#endif
}

