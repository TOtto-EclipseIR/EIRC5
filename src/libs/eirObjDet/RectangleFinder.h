#pragma once
#include "eirObjDet.h"

#include <QObject>

#include <QString>

#include <eirType/QQDir.h>
#include <eirQtCV/cvCascade.h>

#include "RectFinderCatalog.h"

class EIROBJDET_EXPORT RectangleFinder : public QObject
{
    Q_OBJECT
public:
    explicit RectangleFinder(const cvCascade::Type cascadeType, const Settings::Key finderKey, QObject *parent = nullptr);
    QDir baseDir() const;
    bool isLoaded(const cvCascade::Type type);

public slots:
    void initialize();
    void setCascadeBaseDir();
    void readCatalogs();
    void loadCascade(const QString &cascadeXmlFileName);

signals:
    void ctord();
    void initialized();
    void baseDirSet(cvCascade::Type type, QDir cascadeBaseDir);
    void cascadeLoaded(cvCascade::Type type,
                       QFileInfo cascadeXmlFileInfo);

private:
    const cvCascadeType cmType;
    const Settings::Key cmFinderKey;
    const cvCascade cmCascade;
    QQDir mBaseDir;
    RectFinderCatalog mCatalog;

};

