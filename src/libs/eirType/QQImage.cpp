#include "QQImage.h"

#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QImageReader>
#include <QImageWriter>

#include <eirBase/eirBase.h>
#include <eirXfr/Debug.h>

#include "JsonItem.h"
#include "QQPoint.h"
#include "SystemId.h"

QQImage::QQImage() {;}
QQImage::QQImage(const QImage &other) : QImage(other) {;}

QQImage::QQImage(const QString &fileName, const char *format)
    : QImage(fileName, format)
{
    QJsonObject jso;
    SystemId sid(SystemId::Flags(SystemId::SystemInfo
                                 | SystemId::NetworkInfo));
    jso.insert("Input/FileName", fileName);
    jso.insert("Input/SystemId", sid.toJsonObject());
    QJsonDocument jsd(jso);
    setText("JsonInfo", jsd.toJson(QJsonDocument::Compact));
}

QQImage::QQImage(int width, int height, QImage::Format format)
    : QImage(width, height, format)
{
    TRACEQFI << width << height << format;
}

QQImage::QQImage(const uchar *data, int width, int height, QImage::Format format)
{
    TRACEQFI << PTRSTRING(data) << width << height <<  format;
#pragma warning(suppress : 4805)
    if ((qptrdiff(data) & 0x0000001F))
    {
        ERROR << "Qt expects data to be 32-bit aligned";
    }
    else
    {
        QImage newImage(data, width, height, format, format);
        EXPECTNOT(newImage.isNull());
        *this = newImage;
    }
}

void QQImage::nullify()
{
    *this = QImage();
}

int QQImage::rows() const
{
    return size().height();
}

int QQImage::cols() const
{
    return size().width();
}

int QQImage::area() const
{
    return size().area();
}

QQSize QQImage::size() const
{
    return QImage::size();
}

int QQImage::stride() const
{
    return QImage::bytesPerLine();
}

QRgb QQImage::operator[](const int index) const
{
    return ((const QRgb*)(bits()))[index];
}

QRgb &QQImage::operator[](const int index)
{
    return ((QRgb*)(bits()))[index];
}

void QQImage::overlay(const QQImage &other, const Rational opacity)
{
    TRACEQFI << other << opacity;
    convertTo(QImage::Format_ARGB32);
    QQImage ovImage = other.scaled(size()).convertToFormat(QImage::Format_ARGB32);
    for (int index = 0; index < area(); ++index)
        (*this)[index] = (*this)[index] + ((opacity.isNull() ? qAlpha(other[index]) : opacity.toReal()) * other[index]);
}


QStringList QQImage::supportedReadFormats()
{
    QStringList supportedFormatStrings;
    QByteArrayList supportedFormatBAs
            = QImageReader::supportedImageFormats();
    foreach (QByteArray fmt, supportedFormatBAs)
        supportedFormatStrings << QString(fmt);
    return supportedFormatStrings;
}


