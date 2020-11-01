// file: {repo: EIRC2}./src/libs/eirType/Id.h
#pragma once
#include "eirType.h"

#include <QtDebug>

#include <QBitArray>
#include <QList>
#include <QMap>
#include <QStack>
#include <QString>
#include <QUuid>
#include <QVariant>

#include <eirBase/Uuid.h>
#include <eirType/MultiName.h>

#include "Var.h"

class EIRTYPE_EXPORT Id
{
public:
    typedef QList<Id> List;

public:
    Id();
    Id(const quint64 key64,
       const QString &desc=QString(),
       const QVariant &data=QVariant());
    Id(const MultiName &name,
       const quint64 key64,
       const QString &desc=QString(),
       const QVariant &data=QVariant());
    Id(const MultiName &name,
       const QString &desc=QString(),
       const QVariant &data=QVariant());
    ~Id();
    void clear();
    void set(const Uuid &uuid)          { mUuid = uuid; }
    void set(const quint64 key64)       { mU64Key = key64; }
    void set(const MultiName name)      { mNameKey = name; }
    void set(const QString desc)        { mDescription = desc; }
    void set(const QVariant data)       { mData = data; }
    MultiName name() const              { return mNameKey; }
    Uuid uuid() const                   { return mUuid; }
    quint64 key() const                 { return mU64Key; }
    QVariant data() const               { return mData; }
    bool operator <  (const Id & other) const;
    bool operator == (const Id & other) const;
    void remove();
    void insert();
    QString toDebugString() const;

public: // static
    static void remove(const Id &id);
    static void insert(const Id &id);
    static Id newId(const MultiName &name);


private:
    Uuid mUuid;
    quint64 mU64Key;
    MultiName mNameKey;
    QBitArray mFlags;
    QString mDescription;
    QVariant mData;

private: // static
    static QMap<Uuid, Id> smUidIdMap;
    static QMap<quint64, Uuid> smUKeyUidMap;
    static QMap<MultiName, Uuid> smNameUidMap;
};

EIRTYPE_EXPORT QDebug operator<<(QDebug dbg, const Id &id);
