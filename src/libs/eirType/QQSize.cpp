#include "QQSize.h"

#include "QQStringList.h"

QQSize QQSize::null(0,0);

QQSize::QQSize() {;}
QQSize::QQSize(const QSize qsz) : QSize(qsz) {;}
QQSize::QQSize(const QSizeF qszf)
    : QSize(qRound(qszf.width()), qRound(qszf.height())) {;}
QQSize::QQSize(const QQSize &other) : QSize(other.width(), other.height()) {;}
QQSize::QQSize(const int width, const int height) : QSize(width, height) {;}

void QQSize::set(const int width, const int height)
{
    setWidth(width), setHeight(height);
}

void QQSize::set(const QQString &str)
{
    QQStringList qqsl = (str.simplified() + ",,,,").split(',', Qt::KeepEmptyParts);
    int w = qqsl[0].toInt();
    int h = qqsl[1].toInt();
    set(w, h);
}

qreal QQSize::aspect() const
{
    return qreal(width()) / qreal(height());
}

int QQSize::minDimension() const
{
    return qMin(width(), height());
}

int QQSize::area() const
{
    return width() * height();
}

void QQSize::setByWidth(int width, qreal aspect)
{
    QSize::setWidth(width);
    QSize::setHeight(width * aspect);
}

void QQSize::nullify()
{
    setWidth(0), setHeight(0);
}
