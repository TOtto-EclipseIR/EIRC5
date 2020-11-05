#include "ValueMap.h"

ValueMap::ValueMap(const MultiName &name) : mName(name) {;}

Value ValueMap::get(const QString &key) const
{
    return Value(key, mMap.value(key));
}

void ValueMap::set(const QString &key, const QVariant &vari)
{
    mMap.insert(key, vari);
}

QVariant &ValueMap::operator [](const QString &key)
{
    return mMap[key];
}

ValueMap::KeyList ValueMap::keys() const
{
    return MultiName::stringList(mMap.keys());
}

