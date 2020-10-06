// file: {repo: EIRC2}./src/libs/eirType/Id.cpp
#include "Id.h"

#include <QDateTime>

#include <eirXfr/Debug.h>

QMap<Uuid, Id> Id::smUidIdMap;
QMap<quint64, Uuid> Id::smUKeyUidMap;
QMap<MultiName, Uuid> Id::smNameUidMap;

// Id::Id(const Uid uid) : mUid(uid), mU64Key(0) {;}

Id::Id() {;}

Id::Id(const quint64 key64,
       const QString &desc,
       const QVariant &data)
    : mU64Key(key64)
    , mDescription(desc)
    , mData(data) {;}

Id::Id(const MultiName &name,
       const quint64 key64,
       const QString &desc,
       const QVariant &data)
    : mU64Key(key64)
    , mNameKey(name)
    , mDescription(desc)
    , mData(data) {;}

Id::Id(const MultiName &name,
       const QString &desc,
       const QVariant &data)
    : mNameKey(name)
    , mDescription(desc)
    , mData(data) {;}

Id::~Id()
{
    remove();
}

QVariant Id::data() const
{
    return mData;
}

void Id::clear()
{
    TRACEQFI << toString();
    remove();
    mUuid = Uuid(),
            mU64Key = 0,
            mNameKey.clear(),
            mFlags.clear(),
            mDescription.clear(),
            mData.clear();
}

void Id::set(const Uuid &uuid)
{
    mUuid = uuid;
}

void Id::set(const MultiName name)
{
    mNameKey = name;
}

void Id::set(const QVariant data)
{
    mData = data;
}

MultiName Id::name() const
{
    return mNameKey;
}

Uuid Id::uuid() const
{
    return mUuid;
}

QString Id::toString() const
{
    return mNameKey.toString();
}

QString Id::operator ()() const
{
    return toString();
}

bool Id::operator <(const Id &other)
{
    if (mUuid < other.mUuid) return true;
    if (mU64Key < other.mU64Key) return true;
    if (mNameKey < other.mNameKey) return true;
    return false;
}

bool Id::operator ==(const Id &other)
{
    if (mUuid == other.mUuid) return true;
    if (mU64Key == other.mU64Key) return true;
    if (mNameKey == other.mNameKey) return true;
    return false;
}

void Id::remove()
{
    remove(*this);
}

void Id::insert()
{
    insert(*this);
}

void Id::remove(const Id &id)
{
    smUidIdMap.remove(id.mUuid);
    smUKeyUidMap.remove(id.mU64Key);
    smNameUidMap.remove(id.mNameKey);
}

void Id::insert(const Id &id)
{
    smUidIdMap.insert(id.mUuid, id);
    smUKeyUidMap.insert(id.mU64Key, id.mUuid);
    smNameUidMap.insert(id.mNameKey, id.mUuid);
}

Id Id::newId(const MultiName &name)
{
    Id id;
    Uuid newUid;
    while (smUidIdMap.contains(newUid))
    {
        newUid = Uuid();
    };

    id.set(newUid);
    id.set(name);
    id.insert();
    return id;
}
