#include "QQByteArray.h"

#include <eirXfr/Debug.h>

QQByteArray::QQByteArray() {;}

QQByteArray &QQByteArray::operator =(const QByteArray &other)
{
    clear();
    append(other);
    return *this;
}

QString QQByteArray::traceString() const
{
    return QString("QQByteArray %1 bytes: %2")
            .arg(size()).arg(isEmpty() ? "{empty}"
                        : QString::number(*(quint64*)constData()));
}
