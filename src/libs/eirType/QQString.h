// file: {repo: EIRC2}./src/libs/eirType/QQString.h
#pragma once
#include "eirType.h"

#include <QByteArray>
#include <QList>
#include <QString>
#include <QVariant>

class EIRTYPE_EXPORT QQString : public QString
{
public:
    enum Flag
    {
        NoFlag      = 0,
        Simplify    = 0x00000001,
        Squeeze     = 0x00000002,
    };
    Q_DECLARE_FLAGS(Flags, Flag)
    typedef QList<QQString> List;

public:
    QQString(const Flags flags=NoFlag);
    QQString(const QQString &other);
    QQString(const QString &other, const Flags flags=NoFlag);
    QQString(const char *pch, const Flags flags=NoFlag);
    QQString(const QByteArray ba, const Flags flags=NoFlag);
    QQString &operator = (const QQString &other);
    void ctor(void);
    QQString string() const;
    void set(const QString &other);
    QQString squeezed() const;
    QQString appended(const QQString s, const bool delimited=true) const;
    QString operator () () const;
    bool operator == (const QQString &other);
    bool operator <  (const QQString &other);
    operator QVariant() const;

private:
    Flags mFlags=NoFlag;
    static QChar smDelimiter;
};

