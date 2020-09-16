#pragma once
#include "eirObjDet.h"

#include <QObject>

#include <QDir>
#include <QFileInfo>
#include <QString>
#include <QUuid>
#include <QDir>

#include <eirQtCV/cvCascade.h>

#include "ObjDetPak.h"

class EIROBJDET_EXPORT RectangleFinder : public QObject
{
    Q_OBJECT
public:
    explicit RectangleFinder(QObject *parent = nullptr);
    bool isLoaded(const cvCascade::Type type);

public slots:
    void setCascadeBaseDir(const QString &cascadeBaseDirName);
    void loadCascade(const cvCascade::Type type,
                     const QString &cascadeXmlFileName);
    void enqueue(const cvCascade::Type type,
                 const ObjDetPak &pak);

signals:
    void cascadeBaseDirSet(cvCascade::Type type,
                           QDir cascadeBaseDir);
    void cascadeLoaded(cvCascade::Type type,
                       QFileInfo cascadeXmlFileInfo);

};

