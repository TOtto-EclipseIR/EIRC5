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
    QQDir(QString path, const bool datestamp=true);
    QQDir(const QDir &dir, QString path, const bool datestamp=true);
    QQDir &operator = (const QQDir &other);
    bool isNull() const;
    bool notNull() const;
    void setNull(const bool nowNull);
    bool isExistingReadable() const;

    bool mkpath(QString dirPath, const bool datestamp=true);
    bool cd(QString dirName, const bool datestamp=true);
    void setPath(QString path, const bool datestamp=true);

private:
    bool mNull=true;
};

