#pragma once
#include "eirType.h"

#include <QList>

#include "Value.h"
#include "QQString.h"

class EIRTYPE_EXPORT ValueMap
{
public:
    typedef QQString Key;
    typedef QList<Key> KeyList;
    typedef QQString Valu;

    enum Flag
    {
        noFlag          = 0,
        prependGroup    = 0x00000001,
        prependName     = 0x00000002,
        copyName        = 0x00000004,
        appendNameGroup = 0x00000008,
    };
    Q_DECLARE_FLAGS(Flags, Flag);
    
public:
    ValueMap(const MultiName &name=MultiName());
    MultiName name() const          { return mName; }
    bool isEmpty() const            { return mMap.isEmpty();}
    int size() const                { return mMap.size(); }
    bool contains(const Value &vlu) const       
        { return mMap.contains(vlu.name()()); }
    bool contains(const QString &key) const
        { return mMap.contains(key); }
    Value get(const QString &key) const;
    Value get(const Value &vlu) const;
    QVariant get(const QString &key, const QVariant &defVari) const;
    void set(const Value &vlu);
    void set(const QString &key, const QVariant &vari);
    QVariant &at(const QString &key); // non-const reference
    QVariant &operator [] (const QString &key); // non-const reference
    QString beginGroup(const QString &group);
    QString endGroup();
    KeyList keys() const;
    ValueMap extract(const QString &group, const Flags f=noFlag) const;
    void insert(const ValueMap &vmap, const QString &prefix=QString());
    void insert(const Value::List &vlist, const MultiName &prefix=MultiName());
    
private:
    MultiName mName;
    Value::Map mMap;
};

