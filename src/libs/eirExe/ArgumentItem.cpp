#include "ArgumentItem.h"

#include <eirXfr/Debug.h>

ArgumentItem::ArgumentItem(const ArgumentType &argType, const QString &string)
    : cmType(argType)
    , cmString(string)
{
    TRACEQFI << toString();
}

QString ArgumentItem::toString() const
{
    return QString("%1 (%2): %3").arg(cmType.name())
            .arg(cmType()).arg(cmString);
}

QString ArgumentItem::operator ()() const
{
    return toString();
}
