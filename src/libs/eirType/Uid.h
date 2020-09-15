// file: {repo:EIRC2}./src/libs/eirType/Uid.h
#pragma once
#include "eirType.h"

#include <QByteArray>
#include <QList>
#include <QPair>
#include <QString>
#include <QUuid>

#include "UInt128.h"

class EIRTYPE_EXPORT Uuid
{
public:
    typedef QList<Uuid> List;

public:

public:
    Uuid(void);
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
    QByteArray toByteArray(void) const;
    UInt128 toU128(void) const;

public: // static
    static Uuid create();

private:
    QUuid mQUuid;
};

