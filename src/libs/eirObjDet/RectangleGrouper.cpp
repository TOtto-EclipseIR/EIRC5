#include "RectangleGrouper.h"

#include <eirXfr/Debug.h>

RectangleGrouper::RectangleGrouper(const cvCascade::Type cascadeType, const Settings::Key grouperKey, QObject *parent)
    : QObject(parent)
    , cmType(cascadeType)
    , cmGrouperKey(grouperKey)
{
    TRACEQFI << cvCascade::typeName(cascadeType)() << grouperKey() << QOBJNAME(parent);
    setObjectName("RectangleGrouper:"+cvCascade::typeName(cascadeType));
    MUSTDO(it)
}
