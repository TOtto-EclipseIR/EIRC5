#include "ObjectDetection.h"

#include <QCoreApplication>

#include <eirXfr/Debug.h>

#include "ObjDetProcessor.h"

ObjectDetection::ObjectDetection()
    : QObject(qApp->parent())
{
    TRACEFN;
    setObjectName("ObjectDetection");
}

void ObjectDetection::set(const Settings::Key objDetKey)
{
    mObjDetKey = objDetKey();
}

void ObjectDetection::newProcessor(const cvClassifier::Type type)
{
    TRACEQFI << cvClassifier::typeName(type)();
    ObjDetProcessor * oldProc = processor(type);
    if (oldProc)
    {
        oldProc->deleteLater();
        mTypeProcessorMap.remove(type);
    }
    ObjDetProcessor * newProc = new ObjDetProcessor(type, mObjDetKey, this);
    TSTALLOC(newProc);
    mTypeProcessorMap.insert(type, newProc);
    CONNECT(this, &ObjectDetection::processorCreated,
            newProc, &ObjDetProcessor::initialize);
    EMIT(processorCreated(type));
}

ObjDetProcessor *ObjectDetection::processor(const cvClassifier::Type type)
{
    return mTypeProcessorMap[type];
}

void ObjectDetection::initialize()
{
    TRACEQFI << QOBJNAME(this);
    gspClassifierPool->initialize();
    MUSTDO(more?);
    EMIT(setupFinished());
}
