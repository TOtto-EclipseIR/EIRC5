#include "QQSize.h"

QQSize QQSize::null(0,0);

QQSize::QQSize() {;}
QQSize::QQSize(const QSize qsz) : QSize(qsz) {;}
QQSize::QQSize(const QQSize &other) : QSize(other.width(), other.height()) {;}
QQSize::QQSize(const int width, const int height) : QSize(width, height) {;}

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
