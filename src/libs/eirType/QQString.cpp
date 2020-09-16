#include "QQString.h"

QQString::QQString() {;}

QQString::QQString(const QString &other, const Flags flags)
    : QString(other), cmFlags(flags) { ctor(); }

QQString::QQString(const char *pch, const Flags flags)
    : QString(pch), cmFlags(flags) { ctor(); }

void QQString::ctor()
{
    if (cmFlags & Simplify) set(string().simplified());
    if (cmFlags & Squeeze)  set(string().squeezed());
}

QQString QQString::string() const
{
    return mid(0);
}

void QQString::set(const QString &other)
{
    clear();
    append(other);
}

QString QQString::squeezed() const
{
    return mid(0).simplified().replace(QChar(' '), "");
}

QQString::operator QVariant() const
{
    return QVariant(toLocal8Bit());
}
