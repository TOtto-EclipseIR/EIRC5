// file: {repo:EIRC2}./src/libs/eirType/Uid.cpp
#include "Uid.h"

#include <eirXfr/Debug.h>

#include "UInt128.h"

Uuid::Uuid(void) {;}

Uuid::Uuid(const UInt128 u128)
{
    set(u128);
}

Uuid Uuid::set(const UInt128 u128)
{
    TRACEQFI << u128.toHex(true);
    QString s128 = u128.toHex();
    QString sUid = QString("{%1-%2-%3-%4-%5}")
            .arg(s128.mid(0, 8))
            .arg(s128.mid(8, 4))
            .arg(s128.mid(12, 4))
            .arg(s128.mid(16, 4))
            .arg(s128.mid(20, 12));
    TRACE << s128;
    set(sUid);
    return *this;
}

Uuid Uuid::set(const QString &sUid)
{
    mQUuid = QUuid(sUid);
    return *this;
}

Uuid Uuid::create()
{
    QUuid quuid = QUuid::createUuid();
    return Uuid(UInt128(quuid));
}

