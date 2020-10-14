#pragma once
#include "eirObjDet.h"

#include <QObject>

#include <QString>

#include <eirType/QQDir.h>
#include <eirType/QQFileInfo.h>
#include <eirType/QQRectList.h>
#include <eirQtCV/cvClassifier.h>
#include <eirQtCV/cvClassifierPool.h>

#include "RectFinderCatalog.h"

class EIROBJDET_EXPORT RectangleFinder : public QObject
{
    Q_OBJECT
public:
    explicit RectangleFinder(QObject *parent = nullptr);
    explicit RectangleFinder(const cvClassifier::Type cascadeType, const Settings::Key resourceKey,
                             const Settings::Key finderKey, QObject *parent = nullptr);
    cvClassifier::Parameters parameters() const;
    QQString methodString() const;
    QQDir baseDir() const       { return mBaseDir; }
    bool isLoaded() const       { return gspClassifierPool->r(cmType).empty(); }
    XerReturn<QQRectList> findRectangles(const cvMat greyMat, const bool showDetect=false, const QQRect &region=QQRect());

public slots:
    void initialize();
    void setDetectorsBaseDir();
    void readCatalogs();
    void loadCascade();
    void finishSetup();

public: // static

private:
    void loadCascadeFile(const QString &cascadeXmlFileName);
    void loadCascadeFile(const QQFileInfo &cascadeFileInfo);

signals:
    void ctord(const cvClassifier::Type type);
    void initialized(const cvClassifier::Type type);
    void catalogRead(const cvClassifier::Type type, const QQFileInfo qqfi);
    void catalogRead(const cvClassifier::Type type, const Settings::Key key);
    void catalogsRead(const cvClassifier::Type type);
    void baseDirSetup();
    void baseDirSet(const cvClassifier::Type type, const QQDir baseDir);
    void cascadeLoaded(cvClassifier::Type type, QFileInfo cascadeXmlFileInfo);
    void setupFinished(const cvClassifier::Type type);

private:
    void configure();
    void configurePreScan();
    QQRectList preScanMergeRects(const QQRectList &rawRects);

private:
    const cvClassifier::Type cmType;
    const Settings::Key cmResourceKey;
    const Settings::Key cmFinderKey;
    cvClassifier::Parameters mParameters;
    QQDir mBaseDir;
    RectFinderCatalog mCatalog;
};

