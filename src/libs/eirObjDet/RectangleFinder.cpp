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
    CONNECT(this, &RectangleFinder::ctord,
            this, &RectangleFinder::initialize);
    TODO(readCatalogs);
    CONNECT(this, &RectangleFinder::initialized,
            this, &RectangleFinder::setDetectorsBaseDir);
    CONNECT(this, &RectangleFinder::baseDirSetup,
            this, &RectangleFinder::loadCascade);
    CONNECT(this, &RectangleFinder::cascadeLoaded,
            this, &RectangleFinder::setDetectorsBaseDir);
    MUSTDO(it);
    EMIT(ctord(cmType));
}

void RectangleFinder::initialize()
{
    TRACEQFI << QOBJNAME(parent());
    MUSTDO(it);
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
}

void RectangleFinder::finishSetup()
{
    TRACEQFI << QOBJNAME(parent());
    EMIT(setupFinished(cmType));
}

XerReturn<QQRectList> RectangleFinder::findRectangles(const cvMat greyMat, const bool showDetect, const QQRect &region)

{
    TRACEQFI << greyMat.toDebugString() << showDetect << region;
    MUSTDO(configure);
    return classifierPool->r(cmType).detectRectangles(greyMat, mParameters, showDetect, region);
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

