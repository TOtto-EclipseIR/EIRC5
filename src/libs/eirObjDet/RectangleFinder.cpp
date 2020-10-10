#include "RectangleFinder.h"

#include <eirXfr/Debug.h>

RectangleFinder::RectangleFinder(const cvCascade::Type cascadeType, const Settings::Key finderKey, QObject *parent)
    : QObject(parent)
    , cmType(cascadeType)
    , cmFinderKey(finderKey)
    , cmCascade(cascadeType)
{
    TRACEQFI << cvCascade::typeName(cascadeType)() << finderKey() << QOBJNAME(parent);
    setObjectName("RectangleFinder:"+cvCascade::typeName(cascadeType));
    CONNECT(this, &RectangleFinder::ctord,
            this, &RectangleFinder::initialize);
    MUSTDO(it);
    EMIT(ctord());
}

void RectangleFinder::initialize()
{
    TRACEQFI << QOBJNAME(parent());

    MUSTDO(it);
    EMIT(initialized());
}

void RectangleFinder::setCascadeBaseDir()
{
    TRACEQFI << QOBJNAME(parent());

    MUSTDO(it);
    EMIT(baseDirSet());
}

void RectangleFinder::loadCascade(const QString &cascadeXmlFileName)
{
    MUSTUSE(cascadeXmlFileName);
}

