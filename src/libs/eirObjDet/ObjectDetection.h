#pragma once

#include <QObject>

#include <QMap>

#include <eirQtCV/cvCascade.h>

#include "ObjDetProcessor.h"

class ObjectDetection : public QObject
{
    Q_OBJECT
public:
    explicit ObjectDetection(QObject *parent = nullptr);
    ObjDetProcessor * processor(const cvCascadeType type);

signals:
    
private:
    QMap<cvCascadeType, ObjDetProcessor*> mTypeProcessorMap;

};

