// file: {repo: EIRC2}./src/libs/eirType/VarPak.cpp
#include "VarPak.h"

VarPak::VarPak(const Id id) : mId(id) {;}

void VarPak::setValue(const QVariant &data)
{
    id().set(data);
}

void VarPak::set(const Id &id)
{
    mId = id;
}

void VarPak::set(const QByteArray &byteArray)
{
    mBA = byteArray;
}

void VarPak::insert(const VarMap &varMap)
{
    mVarMap.insert(varMap);
}

void VarPak::set(const int index, const Var &listItem)
{
    mVarList.insert(index, listItem);
}

void VarPak::insert(const Var &mapItem)
{
    mVarMap.insert(mapItem);
}

void VarPak::insert(const MultiName &key, const QVariant &value)
{
    insert(Var(key, value));
}

QVariant VarPak::get(const int index) const
{
    return mVarList.value(index).value();
}

Var &VarPak::at(const MultiName &name)
{
    return mVarMap[name];
}

Var VarPak::var(const MultiName &name) const
{
    return mVarMap.value(name.sortable());
}

QVariant VarPak::value(const MultiName &name) const
{
    return mVarMap.value(name.sortable()).value();
}

Id VarPak::id() const
{
    return mId;
}

Id &VarPak::id()
{
    return mId;
}

QByteArray VarPak::bytes() const
{
    return mBA;
}


QDebug operator<<(QDebug dbg, const VarPak &pak)
{
    dbg << pak.id();
    return dbg;
}
