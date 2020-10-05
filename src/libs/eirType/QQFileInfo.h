// file: {repo: EIRC2}./src/libs/eirType/QQFileInfo.h
#pragma once
#include "eirType.h"

#include <QFileInfo>

#include <QList>
#include <QVariant>

#include "QQString.h"

class EIRTYPE_EXPORT QQFileInfo : public QFileInfo
{
public:
    typedef QList<QQFileInfo> List;
public:
    QQFileInfo();
    QQFileInfo(const QQString &filePathName, const QQString::Flags flags=QQString::NoFlag);
    QQFileInfo(const QFileInfo & other);
    QQFileInfo(const QFile & file);
    QQFileInfo(const QDir &dir, const QQString &fileName, const QQString::Flags flags=QQString::NoFlag);
    QQFileInfo(const QDir &dir, const QQString &fileName, const QQString &suffix,
               const QQString::Flags flags=QQString::NoFlag);
    QQFileInfo(const QVariant & variant);
    QQString filePath(const QQString::Flags flags=QQString::NoFlag) const;
    QQString absoluteFilePath(const QQString::Flags flags=QQString::NoFlag) const;
    QQString canonicalFilePath(const QQString::Flags flags=QQString::NoFlag) const;
    QQString fileName(const QQString::Flags flags=QQString::NoFlag) const;
    QQString baseName(const QQString::Flags flags=QQString::NoFlag) const;
    QQString completeBaseName(const QQString::Flags flags=QQString::NoFlag) const;
    QQString suffix(const QQString::Flags flags=QQString::NoFlag) const;
    QQString bundleName(const QQString::Flags flags=QQString::NoFlag) const;
    QQString completeSuffix(const QQString::Flags flags=QQString::NoFlag) const;
    QQString path(const QQString::Flags flags=QQString::NoFlag) const;
    QQString absolutePath(const QQString::Flags flags=QQString::NoFlag) const;
    QQString canonicalPath(const QQString::Flags flags=QQString::NoFlag) const;
    void setFile(const QQString &filePathName);
    void setFile(const QDir &dir, const QQString &fileName);
    void replace(const QQString &trigger, const QQString &with);
    bool isNull() const;
    bool isReadableFile() const;
    bool notExists() const;
    bool notFile() const;
    bool notReadable() const;
    bool tryIsFile(const QIODevice::OpenMode mode=QIODevice::ReadOnly) const;
    bool tryIsDir() const;
    bool tryHasDir() const;
    QQString attributes() const;
    QQString toString() const;
    QVariant toVariant() const;
    operator QVariant () const;
    operator QQString () const;
    QQString operator ()() const;

public: // static
    static bool tryIsFile(const QQString &filePathName,
            const QIODevice::OpenMode mode=QIODevice::ReadOnly);
    static bool tryIsDir(const QQString &pathName);

private:
    bool mIsNull=true;
};
Q_DECLARE_METATYPE(QQFileInfo)
