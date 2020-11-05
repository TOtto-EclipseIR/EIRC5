// file: {repo: EIRC2}./src/libs/eirType/Var.h
#pragma once
#include "eirType.h"

#include <QMap>
#include <QVariant>

#include "MultiName.h"
#include "QQList.h"

class EIRTYPE_EXPORT Var
{
public:
    typedef QQList<Var> List;
    typedef QMap<QString /* MultiName.sortable() */, Var> Map;

public:
    Var(const MultiName & name=MultiName());
    Var(const MultiName & name,
        const QVariant &defValue,
        const QVariant &curValue=QVariant());
    Var(const char * name,
        const QVariant &defValue,
        const QVariant &curValue=QVariant());
    bool isNull() const;
    bool isDefault() const;
    MultiName name() const;
    void set(const MultiName &newName);
    void prependName(const MultiName &groupName);
    QVariant currentVari() const;
    QVariant defaultVari() const;
    QVariant value() const;
    bool operator == (const Var & other);
    QString dumpString() const;
    void dump() const;

private:
    MultiName mName;
    QVariant mDefault;
    QVariant mCurrent;
};
