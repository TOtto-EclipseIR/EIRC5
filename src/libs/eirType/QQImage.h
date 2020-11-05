#pragma once
#include "eirType.h"

#include <QImage>
#include <QJsonDocument>
#include <QStringList>

#include <eirBase/Typedefs.h>

#include "QQSize.h"
#include "Rational.h"

class EIRTYPE_EXPORT QQImage : public QImage
{
public:
    QQImage();
    QQImage(const QImage &other);
    QQImage(const QString &fileName, const char *format = nullptr);
    QQImage(int width, int height, QImage::Format format);
    QQImage(const uchar *data, int width, int height, QImage::Format format);

    void nullify();
    int rows() const;
    int cols() const;
    int area() const;
    QQSize size() const;
    int stride() const;
    QRgb operator[](const int index) const;
    QRgb &operator[](const int index);
    void overlay(const QQImage &other, const Rational opacity=Rational());

private:
    QJsonDocument mDocument;

public: // static
    static QStringList supportedReadFormats();
    static QStringList supportedWriteFormats();
    static QStringList dirNameFilters(const QStringList suffixList);
    static QString dialogNameFilter(const QStringList suffixList);


};



