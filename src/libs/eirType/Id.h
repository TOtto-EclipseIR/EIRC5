// file: {repo: EIRC2}./src/libs/eirType/Id.h
#pragma once
#include "eirType.h"

#include <QBitArray>
#include <QList>
#include <QMap>
#include <QStack>
#include <QString>
#include <QUuid>
#include <QVariant>

#include <eirType/MultiName.h>
#include <eirType/Uid.h>

#include "Var.h"

class EIRTYPE_EXPORT Id
{
public:
    typedef QUuid Uuid;
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
    QVariant data() const;
    void clear();
    void set(const QUuid &uuid);
    void set(const quint64 key64);
    void set(const MultiName name);
    void set(const QString desc);
    void set(const QVariant data);
    MultiName name() const;
    QUuid uuid() const;
    QString toString() const;
    QString operator () () const;
    bool operator <  (const Id & other);
    bool operator == (const Id & other);
    void remove();
    void insert();

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

