#include "MarkManager.h"

#include <eirXfr/Debug.h>

MarkManager::MarkManager(QObject *parent)
    : QObject(parent)
{
    TRACEQFI << QOBJNAME(parent);
    setObjectName("MarkManager");
}
