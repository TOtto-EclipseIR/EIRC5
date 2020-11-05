// file: {repo: EIRC2}./src/libs/eirType/VarMap.cpp
#include "VarMap.h"

#include <QDataStream>

#include <eirXfr/Debug.h>

#include "JsonItem.h"

VarMap::VarMap(const MultiName &name) : mName(name) {;}


VarMap::VarMap(const MultiName &name, const Var::List &vars)
    : mName(name)
{
    foreach (Var var, vars) insert(var);
}

MultiName VarMap::name() const
{
    return mName;
}

void VarMap::setName(const MultiName &name)
{
    mName = name;
}

bool VarMap::contains(const MultiName &name) const
{
    return mVarMap.contains(name.sortable());
}

bool VarMap::notContains(const MultiName &name) const
{
    return ! contains(name);
}

VarMap VarMap::insert(const Var &var)
{
    mVarMap.insert(var.name().sortable(), var);
    return *this;
}

void VarMap::insert(const MultiName &key, const QVariant &vari)
{
    Var v(key, vari, vari);
    insert(v);
}

Var VarMap::value(const MultiName &name) const
{
    return mVarMap.value(name.sortable());
}

MultiName::List VarMap::keys() const
{
    return MultiName::toList(mVarMap.keys());
}

/*
BasicName::List VarMap::groupKeys(const MultiName &groupName)
{
    BasicName::List keyList;
    int nGroupSegments = groupName.segmentCount();
    foreach (Var var, values())
        if (var.name().startsWith(groupName))
        {
            MultiName key = var.name().firstSegmentsRemoved(nGroupSegments);
            keyList.append(key.firstSegment());
        }
    return keyList;

}
*/
VarMap VarMap::extract(const MultiName &groupName) const
{
    TRACEQFI << groupName();
    VarMap extractedMap(groupName);
    int nGroupSegments = groupName.segmentCount();
    foreach (Var var, values())
    {
  //      DUMPVAL(var.name()());
    //    DUMPVAL(var.name().startsWith(groupName));
        if (var.name().startsWith(groupName))
        {
            var.set(var.name().firstSegmentsRemoved(nGroupSegments));
            extractedMap.insert(var);
        }
    }
    return extractedMap;
}

void VarMap::insert(const MultiName &groupName,
                    const VarMap &groupVars)
{
    foreach (Var var, groupVars.values())
    {
        var.prependName(groupName);
        insert(var);
    }
}

void VarMap::insert(const VarMap &other, const bool useMapName)
{
    if (useMapName)
    {
        MultiName mapName = other.name();
        foreach (Var var, other.values())
        {
            Var mapVar = var;
            mapVar.prependName(mapName);
            insert(mapVar);
        }

    }
    else
    {
        foreach (Var var, other.values()) insert(var);
    }
}

void VarMap::operator +=(const VarMap &other)
{
    insert(other);
}

Var::List VarMap::values() const
{
    return mVarMap.values();
}

Var VarMap::var(const MultiName &name) const
{
    return mVarMap.value(name);
}

Var &VarMap::at(const MultiName &name)
{
    return mVarMap[name];
}

Var &VarMap::operator [](const MultiName &name)
{
    return at(name);
}

BasicName::List VarMap::firstSegmentKeys() const
{
    BasicName::List resultList;
    foreach (Var var, values())
    {
        BasicName firstSegment = var.name().firstSegment();
        if ( ! resultList.contains(firstSegment))
            resultList.append(firstSegment);
    }
    return resultList;
}

VarMap VarMap::operator <<  (const Var &var)
{
    return insert(var);
}

QVariant VarMap::toVariant() const
{
    QDataStream ds;
    ds << name().toString();
    ds << mVarMap.size();
    foreach (Var var, mVarMap.values())
    {
        ds << var.name().toString();
        ds << var.currentVari();
        ds << var.defaultVari();
    }
    return QVariant(ds);
}

QJsonObject VarMap::toJsonObject() const
{
    QJsonObject jso;
    MultiName::List mnl = keys();
    foreach (MultiName mn, mnl)
    {
        Var v = value(mn);
        JsonItem ji(mn, v.value().toString());
        jso.insert(mn, ji.toObject());
    }
    return jso;
}

QStringList VarMap::dumpList() const
{
    QStringList qsl;
    foreach(Var var, values())
        qsl << var.dumpString();
    return qsl;
}

void VarMap::dump() const
{
    mName.dump();
    foreach (QString dstr, dumpList()) DUMP << "  " <<dstr;
}

