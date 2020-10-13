#pragma once
#include "eirObjDet.h"

#include <QObject>

#include <QString>

#include <eirType/QQDir.h>
#include <eirQtCV/cvClassifier.h>

#include "RectFinderCatalog.h"

class EIROBJDET_EXPORT RectangleFinder : public QObject
{
    Q_OBJECT
public:
    explicit RectangleFinder(QObject *parent = nullptr);
    explicit RectangleFinder(const cvClassifier::Type cascadeType, const Settings::Key finderKey, QObject *parent = nullptr);
    QDir baseDir() const;
    bool isLoaded(const cvClassifier::Type type);

public slots:
    void initialize();
    void setCascadeBaseDir();
    void readCatalogs();
    void loadCascade(const QString &cascadeXmlFileName);
    void findRectangles(const cvMat greyMat, const bool showDetect=false, const QQRect &region=QQRect());

signals:
    void ctord();
    void initialized();
    void catalogsRead();
    void catalogRead(const QQFileInfo qqfi);
    void baseDirSet(cvClassifier::Type type, QDir cascadeBaseDir);
    void cascadeLoaded(cvClassifier::Type type,
                       QFileInfo cascadeXmlFileInfo);

private:
    const cvClassifier::Type cmType;
    const Settings::Key cmFinderKey;
    cvClassifier::Parameters mParameters;
    QQDir mBaseDir;
    RectFinderCatalog mCatalog;
};

