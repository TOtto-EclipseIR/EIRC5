// file: {repo: EIRC2}./src/libs/eirType/VarMap.h
#pragma once
#include "eirType.h"

#include <QJsonObject>
#include <QList>
#include <QMap>
#include <QStack>

#include "MultiName.h"
#include "Var.h"

class EIRTYPE_EXPORT VarMap
{
public:
    typedef QList<VarMap> List;
    typedef QStack<VarMap> Stack;
    typedef QMap<MultiName, VarMap> Map;

public:
    VarMap(const MultiName &name=MultiName());
    VarMap(const MultiName &name,
           const Var::List & vars);
    MultiName name() const;
    void setName(const MultiName &name);
    bool contains(const MultiName & name) const;
    bool notContains(const MultiName & name) const;
    VarMap insert(const Var &var);
    void insert(const MultiName &key, const QVariant &vari);
    Var value(const MultiName & name) const;
    MultiName::List keys() const;
    //BasicName::List groupKeys(const MultiName &groupName);
    VarMap extract(const MultiName & groupName) const;
    void insert(const MultiName &groupName,
                const VarMap &groupVars);
    void insert(const VarMap &other, const bool useMapName=false);
    void operator += (const VarMap &other);
    Var::List values() const;
    Var var(const MultiName &name) const;
    Var &at(const MultiName &name);
    Var &operator [] (const MultiName &name);
    BasicName::List firstSegmentKeys() const;
    VarMap operator << (const Var &var);
    QVariant toVariant() const;
    QJsonObject toJsonObject() const;
    QStringList dumpList() const;
    void dump() const;

private:
    MultiName mName;
    Var::Map mVarMap;
};

