#pragma once
#include "eirType.h"

#include <QByteArray>

#include <QString>

class EIRTYPE_EXPORT QQByteArray : public QByteArray
{
public:
    QQByteArray();

    QQByteArray &operator=(const QByteArray &other);

    QString traceString() const;
};

