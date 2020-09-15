// file: {repo: EIRC2}./src/libs/eirExe/QQDirIterator.cpp
#include "QQDirIterator.h"

#include <eirXfr/Debug.h>

QQDirIterator::QQDirIterator()
    : mpDirIterator(nullptr) {;}

bool QQDirIterator::isNull() const
{
    return nullptr != mpDirIterator;
}

bool QQDirIterator::notNull() const
{
    return ! isNull();
}

void QQDirIterator::nullify()
{
    TRACEFN
    if (notNull())
    {
        delete mpDirIterator;
        mpDirIterator = nullptr;
    }
}

bool QQDirIterator::start(const QDir &dir)
{
    TRACEQFI << dir;
    nullify();
    QDirIterator * pdi = new QDirIterator(dir);
    if (pdi->hasNext())
    {
        mpDirIterator = pdi;
    }
    TRACEQFI << "return" << notNull();
    return notNull();
}

bool QQDirIterator::hasNext() const
{
    return isNull() ? false : mpDirIterator->hasNext();
}

void QQDirIterator::goNext()
{
    if (notNull()) mpDirIterator->next();
}

QFileInfo QQDirIterator::fileInfo() const
{
    return notNull() ? mpDirIterator->fileInfo() : QFileInfo();
}


