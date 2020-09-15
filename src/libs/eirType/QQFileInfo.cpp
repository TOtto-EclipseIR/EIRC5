// file: {repo: EIRC2}./src/libs/eirType/QQFileInfo.h
#include "QQFileInfo.h"

#include <QDir>

#include <eirXfr/Debug.h>

#include "Milliseconds.h"

QQFileInfo::QQFileInfo() {;}
QQFileInfo::QQFileInfo(const QQString &filePathName, const QQString::Flags flags)
    : QFileInfo(QQString(filePathName, flags)), mIsNull(false) {;}
QQFileInfo::QQFileInfo(const QFileInfo &other)
    : QFileInfo(other), mIsNull(false) {;}
QQFileInfo::QQFileInfo(const QFile &file)
    : QFileInfo(file), mIsNull(false) {;}

QQFileInfo::QQFileInfo(const QDir &dir, const QQString &fileName, const QQString::Flags flags)
{
    setFile(dir, QQString(fileName, flags));
}

QQFileInfo::QQFileInfo(const QVariant &variant)
{
    *this = variant.value<QQFileInfo>();
}

QQString QQFileInfo::filePath(const QQString::Flags flags) const
{
    return QQString(QFileInfo::filePath(), flags);
}

QQString QQFileInfo::absoluteFilePath(const QQString::Flags flags) const
{
    return QQString(QFileInfo::absoluteFilePath(), flags);
}

QQString QQFileInfo::fileName(const QQString::Flags flags) const
{
    return QQString(QFileInfo::fileName(), flags);
}

QQString QQFileInfo::completeBaseName(const QQString::Flags flags) const
{
    return QQString(QFileInfo::completeBaseName(), flags);
}

QQString QQFileInfo::absolutePath(const QQString::Flags flags) const
{
    return QQString(QFileInfo::absolutePath(), flags);
}

void QQFileInfo::setFile(const QQString &filePathName)
{
    TRACEQFI << filePathName;
    mIsNull = false;
    QFileInfo::setFile(filePathName);
    replace("@", Milliseconds::baseDateStamp());
    TRACE << QFileInfo::filePath();
}

void QQFileInfo::setFile(const QDir &dir, const QQString &fileName)
{
    TRACEQFI << dir << fileName;
    mIsNull = false;
    QFileInfo fi(dir, fileName);
    QQString filePathName = fi.filePath();
    setFile(filePathName);
    TRACE << QFileInfo::filePath();
}

void QQFileInfo::replace(const QQString &trigger, const QQString &with)
{
    TRACEQFI << trigger << with;
    QQString filePathName = filePath();
    filePathName.replace(trigger, with);
    QFileInfo::setFile(filePathName);
    TRACE << QFileInfo::filePath();
}

bool QQFileInfo::isNull() const
{
    return mIsNull;
}

bool QQFileInfo::tryIsFile(const QIODevice::OpenMode mode) const
{
    TRACEQFI << absoluteFilePath();
    bool canOpenFile = tryIsFile(absoluteFilePath(), mode);
    TRACERTN(canOpenFile);
    return canOpenFile;
}

bool QQFileInfo::tryIsDir() const
{
    QQString absolutePath = dir().absolutePath();
    TRACEQFI << absolutePath;
    bool canCdDir = tryIsDir(absolutePath);
    TRACERTN(canCdDir);
    return canCdDir;
}

QQString QQFileInfo::attributes() const
{
    if (isNull()) return "isNull ";
    QQString attribString;
    if (isAbsolute())       attribString += "Absolute ";
    if (tryIsDir())         attribString += "Dir ";
    if (isExecutable())     attribString += "Executable ";
    if (tryIsFile())        attribString += "File ";
    if (isReadable())       attribString += "Readable ";
    if (isRoot())           attribString += "Root ";
    if (isWritable())       attribString += "Writable ";
    return attribString.simplified();
}

QQString QQFileInfo::toString() const
{
    if (tryIsDir())     return absolutePath();
    if (tryIsFile())    return absoluteFilePath();
    return fileName();
}

QVariant QQFileInfo::toVariant() const
{
    return QVariant::fromValue(*this);
}

QQFileInfo::operator QVariant() const
{
    return toVariant();
}

QQFileInfo::operator QQString() const
{
    return toString();
}

QQString QQFileInfo::operator ()() const
{
    return toString();
}

/* -------- static public --------------------------------- */

bool QQFileInfo::tryIsFile(const QQString &filePathName,
                           const QIODevice::OpenMode mode)
{
    TRACEQFI << filePathName;
    QFile file(filePathName);
    bool canOpenFile = file.open(QIODevice::ExistingOnly | mode);
    TRACERTN(canOpenFile);
    return canOpenFile;
}

bool QQFileInfo::tryIsDir(const QQString &pathName)
{
    TRACEQFI << pathName;
    QDir tryDir;
    bool canCdDir = tryDir.cd(pathName);
    TRACERTN(canCdDir)
    return canCdDir;
}


