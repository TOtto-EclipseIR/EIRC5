#pragma once

#include <QObject>

#include <QMap>

#include <eirExe/Settings.h>
#include <eirQtCV/cvClassifier.h>

class ObjDetProcessor;

class ObjectDetection : public QObject
{
    Q_OBJECT
public:
    explicit ObjectDetection();
    ObjDetProcessor *newProcessor(const cvClassifier::Type type);
    ObjDetProcessor *processor(const cvClassifier::Type type);

signals:
    
private:
    QMap<cvClassifier::Type, ObjDetProcessor*> mTypeProcessorMap;
    Settings::Key mObjDetKey;
};
Q_GLOBAL_STATIC(ObjectDetection, OBJD);

