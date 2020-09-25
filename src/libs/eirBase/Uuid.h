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
    Uuid(const Uuid &other);
    Uuid(const QUuid &other);
    Uuid &operator = (const Uuid &other);
    void set(const QUuid &other);
    QUuid toUuid() const;
    QByteArray toByteArray(void) const;
    UInt128 toU128(void) const;
    QString trace() const;

public: // static

private:
    QUuid mQUuid;
};

template<class T> QMap<Uuid, T> UuidTMap;

