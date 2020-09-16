#include "QQFile.h"

#include <eirXfr/Debug.h>

QQFile::QQFile()
{

}

/* ------- static ----------------------------------------- */

QByteArray QQFile::readAll(const QQFileInfo &fileInfo)
{
    TRACEQFI << fileInfo;
    EXPECT(fileInfo.exists());
    EXPECT(fileInfo.isFile());
    EXPECT(fileInfo.isReadable());
    QFile * file = new QFile(fileInfo.absoluteFilePath());
    TSTALLOC(file);
    EXPECT(file->open(QIODevice::ExistingOnly | QIODevice::ReadOnly));
    return (file->isReadable()) ? file->readAll() : QByteArray();
}
