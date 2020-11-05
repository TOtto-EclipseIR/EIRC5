#include "ActionManager.h"

#include <eirXfr/Debug.h>

ActionManager::ActionManager(QObject *parent)
    : QObject(parent)
{
    TRACEQFI << QOBJNAME(parent);
    setObjectName("ActionManager");
}
