// file: {repo: EIRC2}./src/libs/eirType/VarPak.h
#pragma once
#include "eirType.h"

#include <QList>
#include <QMap>
#include <QStack>

#include "Id.h"
#include "MultiName.h"
#include "Var.h"
#include "VarMap.h"


typedef Var::List VarList; // TODO? Make this its own class later

class EIRTYPE_EXPORT VarPak
{
public:
    VarPak(const Id id=Id());
    void setValue(const QVariant & data);
    void set(const Id &id);
    void set(const QByteArray &byteArray);
    void set(const Var::List &varList);
    void insert(const VarMap &varMap);
    void set(const int index, const Var &listItem);
    void append(const Var &listItem);
    void insert(const Var &mapItem);
    void insert(const MultiName &key,
                const QVariant &value);
    QVariant get(const int index) const;
    Var &at(const MultiName &name);
    Var var(const MultiName &name) const;
    QVariant value(const MultiName &name) const;
    Id id() const;
    Id &id();  // non-const
    QByteArray bytes() const;
    VarList list() const;
    VarList & list(); // non-const
    VarMap map() const;
    VarMap & map(); // non-const

private:
    Id mId;
    QByteArray mBA;
    Var::List mVarList;
    VarMap mVarMap;
};

EIRTYPE_EXPORT QDebug operator<<(QDebug dbg, const VarPak &pak);

