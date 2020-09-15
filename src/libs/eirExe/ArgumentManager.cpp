#include "ArgumentManager.h"

#include <eirXfr/Debug.h>

ArgumentManager::ArgumentManager(QObject *parent) : QObject(parent)
{
    TRACEQFI << QOBJNAME(parent);
}

void ArgumentManager::enqueue(const ArgumentItem &item)
{
    TRACEQFI << item.toString();
    mItemList.append(item);
}

void ArgumentManager::enqueue(const ArgumentItem::List &items)
{
    TRACEQFI << items.size();
    foreach (ArgumentItem item, items) enqueue(item);
}
