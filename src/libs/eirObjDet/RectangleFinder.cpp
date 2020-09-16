#include "RectangleFinder.h"

#include <eirXfr/Debug.h>

RectangleFinder::RectangleFinder(QObject *parent) : QObject(parent)
{
    MUSTDO(it);
}

void RectangleFinder::setCascadeBaseDir(const QString &cascadeBaseDirName)
{
    MUSTUSE(cascadeBaseDirName);
}

void RectangleFinder::loadCascade(const cvCascade::Type type, const QString &cascadeXmlFileName)
{
    MUSTUSE(type); MUSTUSE(cascadeXmlFileName);
}

void RectangleFinder::enqueue(const cvCascade::Type type, const ObjDetPak &pak)
{
    MUSTUSE(type); MUSTUSE(pak);
}
