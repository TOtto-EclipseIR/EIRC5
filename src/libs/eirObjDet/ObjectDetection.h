#pragma once

#include <QObject>

#include <QMap>

#include <eirQtCV/cvClassifier.h>

#include "ObjDetProcessor.h"

class ObjectDetection : public QObject
{
    Q_OBJECT
public:
    explicit ObjectDetection(QObject *parent = nullptr);
    ObjDetProcessor * processor(const cvClassifier::Type type);

signals:
    
private:
    QMap<cvClassifier::Type, ObjDetProcessor*> mTypeProcessorMap;

};

