#include "ValuePak.h"

#include <eirXfr/Debug.h>

ValuePak::ValuePak()
{

}

void ValuePak::clear()
{
    TRACEFN;
    mId.clear(),
            mBA.clear(),
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

void ValuePak::set(const QByteArray &byteArray)
{
    mBA = byteArray;
}

void ValuePak::set(const int index, const Value &mapItem)
{
    at(index) = mapItem;
}

Value &ValuePak::at(const int index)
{
    return mValueList[index];
}

Value ValuePak::at(const int index) const
{
    return mValueList[index];
}

QVariant ValuePak::value(const int index) const
{
    return at(index).second;
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

QByteArray ValuePak::bytes() const
{
    return mBA;
}

QVariant ValuePak::operator()(const int index) const
{
    return at(index).second;
}
