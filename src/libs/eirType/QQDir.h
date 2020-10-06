#pragma once
#include "eirType.h"

#include <QDir>

class EIRTYPE_EXPORT QQDir : public QDir
{
public:
    QQDir();
    QQDir(const QDir &other);
    QQDir(const QString &path);
    QQDir(const QDir &dir, const QString &path);
    QQDir &operator = (const QDir &other);
    bool isNull() const;
    bool notNull() const;
    void setNull(const bool nowNull);

    bool cd(const QString &dirName);
    void setPath(const QString &path);

private:
    bool mNull=true;
};

