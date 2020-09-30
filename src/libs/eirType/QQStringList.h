// file: {repo: EIRC2}./src/libs/eirType/QQString.h
#pragma once
#include "eirType.h"

#include <QList>
#include "QQString.h"

class EIRTYPE_EXPORT QQStringList : public QQString::List
{
public:
    QQStringList();
    QQStringList(const QStringList &other);
    void prepend(const QQStringList &other);
    QQString join(const QQString &separator) const;
    bool notEmpty() const;
};

