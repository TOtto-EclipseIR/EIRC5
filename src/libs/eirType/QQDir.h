#pragma once
#include "eirType.h"

#include <QDir>

#include <QVector>

class EIRTYPE_EXPORT QQDir : public QDir
{
public:
    typedef QVector<QQDir> Vector;
public:
    QQDir();
    QQDir(const QDir &other);
    QQDir(const QString &path);
    QQDir(const QDir &dir, const QString &path);
    QQDir &operator = (const QQDir &other);
    bool isNull() const;
    bool notNull() const;
    void setNull(const bool nowNull);

    bool mkpath(const QString &dirPath);
    bool cd(const QString &dirName);
    void setPath(const QString &path);

private:
    bool mNull=true;
};

