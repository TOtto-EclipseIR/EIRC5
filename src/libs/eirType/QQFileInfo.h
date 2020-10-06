// file: {repo: EIRC2}./src/libs/eirType/QQFileInfo.h
#pragma once
#include "eirType.h"

#include <QFileInfo>

#include <QList>


class EIRTYPE_EXPORT QQFileInfo : public QFileInfo
{
public:
    typedef QList<QQFileInfo> List;
public:
    QQFileInfo();
    QQFileInfo(const QString &filePathName);
    QQFileInfo(const QFileInfo & other);
    QQFileInfo(const QFile & file);
    QQFileInfo(const QDir &dir, const QString &fileName);
    void setFile(const QString &filePathName);
    void setFile(const QDir &dir, const QString &fileName);
    void replace(const QString &trigger, const QString &with);
    bool isNull() const;
    bool tryIsFile(const QIODevice::OpenMode mode
                            =QIODevice::ReadOnly) const;
    bool tryIsDir() const;
    QString attributes() const;
    QString toString() const;
    operator QString () const;
    QString operator ()() const;
public: // static
    static bool tryIsFile(const QString &filePathName,
            const QIODevice::OpenMode mode=QIODevice::ReadOnly);
    static bool tryIsDir(const QString &pathName);

private:
    bool mIsNull=true;
};

