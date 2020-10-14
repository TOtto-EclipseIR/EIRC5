#pragma once
#include "eirObjDet.h"

#include <QObject>

#include <QMap>

#include <eirExe/Settings.h>
#include <eirQtCV/cvClassifier.h>

class ObjDetProcessor;

class EIROBJDET_EXPORT ObjectDetection : public QObject
{
    Q_OBJECT
public:
    explicit ObjectDetection();
    ObjDetProcessor *processor(const cvClassifier::Type type);

public slots:
    void initialize();
    void newProcessor(const cvClassifier::Type type);

signals:
    void setupFinished();
    
private:
    QMap<cvClassifier::Type, ObjDetProcessor*> mTypeProcessorMap;
    Settings::Key mObjDetKey;
};
Q_GLOBAL_STATIC(ObjectDetection, OBJD);

