#include "ArgumentItem.h"

#include <eirXfr/Debug.h>

ArgumentItem::ArgumentItem(const BasicName &name)
    : Id(Id::newId(name))
//    , cmName(name)
{
    TRACEQFI << /*name() <<*/ toString();
}
