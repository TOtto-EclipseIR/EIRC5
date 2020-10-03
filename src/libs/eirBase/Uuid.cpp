#include "Uuid.h"

#include <QDateTime>

#include <eirXfr/Debug.h>

Uuid::Uuid(): QUuid(QUuid::createUuid()) {;}
Uuid::Uuid(const QUuid &other) : QUuid(other) {;}
Uuid::Uuid(const Uuid &other) : QUuid(other.toUuid()) {;}

Uuid &Uuid::operator =(const Uuid &other)
{
    set(other.toUuid());
    return *this;
}

void Uuid::set(const QUuid &other)
{
    this->fromString(other.toString());
}

QUuid Uuid::toUuid() const
{
    return *this;
}

QString Uuid::trace() const
{
    return toString(QUuid::WithBraces).right(14);
}
