#include "JsonItem.h"

#include "eirXfr/Debug.h"

JsonItem::JsonItem()
{
    TRACEFN;
}

JsonItem::JsonItem(const MultiName &key, const QString &svalue)
    : QJsonValue(svalue)
    , mName(key)
{
    TRACEQFI << key() << svalue;
}

QJsonObject JsonItem::toObject() const
{
    QJsonObject qjo;
    qjo.insert(mName.toString(), QJsonValue(*this));
    return qjo;
}
