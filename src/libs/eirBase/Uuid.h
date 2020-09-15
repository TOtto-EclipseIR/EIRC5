#pragma once
#include "eirBase.h"

#include <QMap>
#include <QQueue>
#include <QUuid>
#include <QVariant>

#include "UInt128.h"

class EIRBASE_EXPORT Uuid : public QUuid
{
public:
    typedef QList<Uuid> List;
    typedef QQueue<Uuid> Queue;
    typedef QMap<Uuid, QVariant> Map;

public:
    Uuid();
    /*
    Uuid(const UInt128 u128);
    Uuid(const QString & sUid,
        const QUuid::StringFormat fmt,
        const QUuid::Version ver=QUuid::Time,
        const QUuid::Variant var=QUuid::DCE);
    Uuid(const QByteArray & rawUid,
        const QUuid::Version ver=QUuid::Time,
        const QUuid::Variant var=QUuid::DCE);

    Uuid set(const UInt128 u128);
    Uuid set(const QString & sUid);
    Uuid set(const QByteArray & rawUid,
            const QUuid::Version ver=QUuid::Time,
            const QUuid::Variant var=QUuid::DCE);
    */
    QUuid toUuid() const;
    QByteArray toByteArray(void) const;
    UInt128 toU128(void) const;
    QString trace() const;

public: // static
//    static Uuid create();

private:
    QUuid mQUuid;
};

template<class T> QMap<Uuid, T> UuidTMap;

