// file: {EIRC2 Repo}./src/libs/eirExe/FileName.cpp
#include "FileName.h"

#include <eirXfr/Debug.h>

QDateTime FileName::smBaseDateTime=QDateTime::currentDateTime();

FileName::FileName(const QString &qstr)
{
    TRACEQFI << qstr;
    setBase(qstr);
}

void FileName::set(const QString &qstr,
                   const QDateTime &dateTime)
{
    TRACEQFI << qstr << dateTime;
    mString = qstr;
    mDateTime = dateTime;
}

void FileName::setBase(const QString &qstr)
{
    TRACEQFI << qstr;
    mString = qstr;
    mDateTime = smBaseDateTime;
}

void FileName::setCurrent(const QString &qstr)
{
    TRACEQFI << qstr;
    mString = qstr;
    mDateTime = QDateTime::currentDateTime();
}

QString FileName::toString(const QString &format) const
{
    QString r = mString;
    r.replace('@', format.isEmpty()
                            ? "-DyyyyMMdd-Thhmmsszzz"
                            : format,
                           Qt::CaseSensitive);
    return r;
}

QString FileName::operator ()() const
{
    return toString();
}

FileName::operator QString() const
{
    return toString();
}
