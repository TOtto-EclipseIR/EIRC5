#include "QQDir.h"

#include <eirXfr/Debug.h>

QQDir::QQDir() : mNull(true) {;}
QQDir::QQDir(const QDir &other) : QDir(other), mNull(false) {;}
QQDir::QQDir(const QString &path) : QDir(path), mNull(false) {;}

QQDir::QQDir(const QDir &dir, const QString &path)
    : QDir(path)
    , mNull(false)
{
    TRACEQFI << dir << path;
    MUSTDO(Testing);
    QDir::setPath(path);
}

QQDir &QQDir::operator =(const QDir &other)
{
    QDir::setPath(other.path());
    mNull = QDir::exists();
    return *this;
}

bool QQDir::isNull() const
{
    return mNull;
}

bool QQDir::notNull() const
{
    return ! isNull();
}

void QQDir::setNull(const bool nowNull)
{
    mNull = nowNull;
}

bool QQDir::cd(const QString &dirName)
{
    TRACEQFI << dirName;
    mNull = QDir::cd(dirName);
    return mNull;
}

void QQDir::setPath(const QString &path)
{
    TRACEQFI << path;
    QDir::setPath(path);
    mNull = QDir::exists();
}
