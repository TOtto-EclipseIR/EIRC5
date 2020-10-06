// file: {repo: EIRC2}./src/libs/eirType/ValuePak.h
#pragma once
#include "eirType.h"

#include <QList>
#include <QMap>
#include <QStack>
#include <QVariant>
#include <QVariantList>

#include <eirType/QQByteArray.h>

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
    bool contains(const MultiName &key) const;
    bool notContains(const MultiName &key) const;
    void set(const Id &id);
    void set(const QQByteArray &byteArray);
    void set(const int index, const QVariant value);
    void set(const MultiName &key, const QVariant value);
    void insert(const Value::Map &valueMap);
    void append(const Value &listItem);
    void insert(const Value &mapItem);
    QVariant &at(const int index); // non-const
    QVariant at(const int index) const;
    QVariant &at(const MultiName &name); // non-const
    QVariant at(const MultiName &name) const;
    MultiName::List keys(const MultiName &groupName, const bool recurse=false);
    Id id() const;
    Id &id();
    Uuid uuid() const;
    QQByteArray bytes() const;
    Value::Map map() const;
    Value::Map &map(); // non-const
    QVariant operator()(const int index) const;
    QVariant operator()(const MultiName &name) const;

protected:
    void resizeList(const int index);

private:
    Id mId;
    QQByteArray mBytes;
    QVariantList mValueList;
    Value::Map mValueMap;
};

