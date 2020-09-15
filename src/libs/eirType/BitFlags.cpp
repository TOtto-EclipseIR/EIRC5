//! \file Flags.cpp
#include "BitFlags.h"

#include <eirXfr/Debug.h>

BitFlags::BitFlags(const int sz, const bool iz)
{
    TRACEQFI << sz << iz;
    resize(sz, true);
    EXPECTEQ(sz, size());
    fill(iz);
    EXPECT(isAll(iz));
}

int BitFlags::size() const
{
    return mBits.size();
}

void BitFlags::resize(const int newSize, const bool truncate)
{
    if (truncate)
        for (int index = newSize; index < size(); ++index)
            remove(namePch(index));
    if (truncate || newSize > size())
        mBits.resize(newSize);
}

void BitFlags::fill(const bool is)
{
    mBits.fill(is);
}

bool BitFlags::isAll(const bool is) const
{
    bool isNot = ! is;
    for (int index = 0; index < size(); ++index)
        if (isNot == at(index)) return false;
    return true;
}

bool BitFlags::at(const int index) const
{
    return mBits.at(index);
}

void BitFlags::registerFlag(const int newIndex, const BasicName &name)
{
//    TRACEQFI << newIndex << name();
    WEXPECTNOT(mIndexNameDMap.contains(newIndex));
    WEXPECTNOT(mIndexNameDMap.contains(name));
    mIndexNameDMap.insertUnique(newIndex, name);
    mBits[newIndex] = false;
}

void BitFlags::registerFlag(const BasicName &name)
{
    const int index = mIndexNameDMap.size();
    registerFlag(index, name);
}

void BitFlags::registerFlags(const int newIndex, const BasicName::List &names)
{
    int index = newIndex;
    foreach (BasicName name, names)
        registerFlag(index++, name);
}

void BitFlags::registerFlags(const int newIndex, const QStringList &names)
{
    TRACEQFI << newIndex << names;
    NEEDDO(it) NEEDUSE(newIndex) NEEDUSE(names)
}

void BitFlags::registerFlags(const int newIndex, QString &names)
{
    registerFlags(newIndex, BasicName::listFrom(names));
}

BasicName BitFlags::name(const int index) const
{
    return mIndexNameDMap.at(index);
}

const char *BitFlags::namePch(const int index) const
{
    return name(index)().toLocal8Bit();
}
