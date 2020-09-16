// file: {repo: EIRC2}./src/libs/eirType/QQString.h
#pragma once
#include "eirType.h"

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

public:
    QQString();
    QQString(const QString &other, const Flags flags=NoFlag);
    QQString(const char *pch, const Flags flags=NoFlag);
    void ctor(void);
    QQString string() const;
    void set(const QString &other);
    QString squeezed() const;
    operator QVariant () const;

private:
    const Flags cmFlags;
};

