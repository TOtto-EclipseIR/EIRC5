#include "QQString.h"

QChar QQString::smDelimiter=QChar('/');

QQString::QQString(const Flags flags) : mFlags(flags) {;}
QQString::QQString(const QQString &other)
    : QString(other), mFlags(NoFlag) { ctor(); }
QQString::QQString(const QString &other, const Flags flags)
    : QString(other), mFlags(flags) { ctor(); }
QQString::QQString(const char *pch, const Flags flags)
    : QString(pch), mFlags(flags) { ctor(); }
QQString::QQString(const QByteArray ba, const Flags flags)
    : QString(ba), mFlags(flags) { ctor(); }

QQString &QQString::operator =(const QQString &other)
{
    set(other.string()), mFlags = other.mFlags;
    return *this;
}

void QQString::ctor()
{
    if (mFlags & Simplify) set(string().simplified());
    if (mFlags & Squeeze)  set(string().squeezed());
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

QString QQString::operator ()() const
{
    return string();
}

QQString QQString::squeezed() const
{
    return mid(0).simplified().replace(QChar(' '), "");
}

QQString QQString::appended(const QQString s, const bool delimited) const
{
    QQString rtn = string();
    if (delimited && smDelimiter != s[0]) rtn.append(smDelimiter);
    return rtn + s;
}

bool QQString::operator ==(const QQString &other)
{
    return isNull() == other.isNull() && string() == other.string();
}

bool QQString::operator <(const QQString &other)
{
    return string().mid(0) < other.mid(0);
}

QQString::operator QVariant() const
{
    return QVariant(toLocal8Bit());
}
