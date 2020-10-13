#include "RectangleGrouper.h"

#include <eirXfr/Debug.h>

RectangleGrouper::RectangleGrouper(const cvClassifier::Type cascadeType, const Settings::Key grouperKey, QObject *parent)
    : QObject(parent)
    , cmType(cascadeType)
    , cmGrouperKey(grouperKey)
{
    TRACEQFI << cvClassifier::typeName(cascadeType)() << grouperKey() << QOBJNAME(parent);
    setObjectName("RectangleGrouper:"+cvClassifier::typeName(cascadeType));
    MUSTDO(it)
}
