#include "QQDir.h"

#include <eirXfr/Debug.h>

#include "Milliseconds.h"

QQDir::QQDir() : mNull(true) {;}
QQDir::QQDir(const QDir &other) : QDir(other), mNull(false) {;}

QQDir::QQDir(QString path, const bool datestamp)
{
    TRACEQFI << path;
    if (datestamp)
        path.replace("@", Milliseconds::baseDateStamp());
    setPath(path);
}

QQDir::QQDir(const QDir &dir, QString path, const bool datestamp)
{
    TRACEQFI << dir << path;
    if (datestamp) path.replace("@", Milliseconds::baseDateStamp());
    QDir::setPath(path);
}

QQDir &QQDir::operator =(const QQDir &other)
{
    QDir::setPath(other.path());
    mNull = other.mNull;
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

bool QQDir::isExistingReadable() const
{
    return exists() && isReadable();
}

bool QQDir::mkpath(QString dirPath, const bool datestamp)
{
    TRACEQFI << dirPath;
    if (datestamp) dirPath.replace("@", Milliseconds::baseDateStamp());
    mNull = QDir::mkpath(dirPath);
    return mNull;
}

bool QQDir::cd(QString dirName, const bool datestamp)
{
    TRACEQFI << dirName;
    if (datestamp) dirName.replace("@", Milliseconds::baseDateStamp());
    mNull = QDir::cd(dirName);
    return mNull;
}

void QQDir::setPath(QString path, const bool datestamp)
{
    TRACEQFI << path;
    if (datestamp) path.replace("@", Milliseconds::baseDateStamp());
    QDir::setPath(path);
    mNull = QDir::exists();
}
