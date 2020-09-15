// file: {repo: EIRC2}./src/libs/eirType/ValuePak.h
#pragma once
#include "eirType.h"

#include <QList>
#include <QMap>
#include <QStack>

#include "Id.h"
#include "MultiName.h"
#include "Value.h"

class EIRTYPE_EXPORT ValuePak
{
public:
    ValuePak();
    ValuePak(const Id id);
    void clear();
    bool contains(const int index) const;
    bool notContains(const int index) const;
    void set(const Id &id);
    void set(const QByteArray &byteArray);
    void set(const Value::List &varList);
    void insert(const Value::Map &valueMap);
    void set(const int index, const Value &mapItem);
    void append(const Value &listItem);
    void insert(const Value &mapItem);
    void insert(const MultiName &key,
                const QVariant &value);
    Value &at(const int index); // non-const
    Value at(const int index) const;
    Value &at(const MultiName &name); // non-const
    Value at(const MultiName &name) const;
    QVariant value(const int index) const;
    QVariant value(const MultiName &name) const;
    MultiName::List keys(const MultiName &groupName, const bool recurse=false);
    Id id() const;
    Id &id();
    Uuid uuid() const;
    QByteArray bytes() const;
    Value::List list() const;
    Value::List & list(); // non-const
    Value::Map map() const;
    Value::Map & map(); // non-const
    Value &operator[](const int index); // non-const
    Value operator[](const int index) const;
    Value &operator[](const MultiName &name); // non-const
    Value operator[](const MultiName &name) const;
    QVariant operator()(const int index) const;
    QVariant operator()(const MultiName &name) const;

private:
    Id mId;
    QByteArray mBA;
    Value::List mValueList;
    Value::Map mValueMap;
};

