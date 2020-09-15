#include "ValuePak.h"

#include <eirXfr/Debug.h>

ValuePak::ValuePak() {;}
ValuePak::ValuePak(const Id id) : mId(id) {;}

void ValuePak::clear()
{
    TRACEFN;
    mId.clear(),
            mBytes.clear(),
            mValueList.clear(),
            mValueMap.clear();
}

bool ValuePak::contains(const int index) const
{
    return mValueList.size() > index && index >= 0;
}

bool ValuePak::notContains(const int index) const
{
    return ! contains(index);
}

void ValuePak::set(const QQByteArray &byteArray)
{
    mBytes = byteArray;
}

void ValuePak::set(const int index, const QVariant value)
{
    if (notContains(index)) resizeList(index);
    mValueList.replace(index, value);
}

void ValuePak::set(const MultiName &key, const QVariant value)
{
    mValueMap.insert(key, value);
}

QVariant ValuePak::at(const int index) const
{
    return contains(index) ? mValueList.at(index) :QVariant();
}

QVariant &ValuePak::at(const MultiName &name)
{
    return mValueMap[name];
}

QVariant ValuePak::at(const MultiName &name) const
{
    return mValueMap.value(name);
}

MultiName::List ValuePak::keys(const MultiName &groupName,
                               const bool recurse)
{
    TRACEQFI << groupName() << recurse;
    MultiName::List result;
    int groupSegments = groupName.segmentCount();
    foreach (MultiName key, mValueMap.keys())
        if (groupName == key.firstSegments(groupSegments))
            if (recurse || key.segmentCount() == groupSegments)
            {
                TRACE << key();
                result.append(key);
            }
    return result;
}

Id ValuePak::id() const
{
    return mId;
}

Id &ValuePak::id()
{
    return mId;
}

Uuid ValuePak::uuid() const
{
    return mId.uuid();
}

QQByteArray ValuePak::bytes() const
{
    return mBytes;
}

QVariant ValuePak::operator()(const int index) const
{
    return at(index);
}

/* --------- protected ------------------------------------ */

void ValuePak::resizeList(const int index)
{
    while (mValueList.size() <= index)
        mValueList.append(QVariant());
}
