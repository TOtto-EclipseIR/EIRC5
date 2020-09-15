#include "QQRectF.h"

QQRectF::QQRectF() {;}

QQRectF::QQRectF(qreal x, qreal y, qreal width, qreal height)
    : QRectF(x, y, width, height) {;}

QQRectF::QQRectF(const QSizeF size, const QPointF center)
    : QRectF(center.x() - size.width()  / 2,
             center.y() - size.height() / 2,
             size.height(), size.width()) {;}

QQRectF::QQRectF(const QRect qrect)
    : QRectF(qreal(qrect.x()), qreal(qrect.y()),
             qreal(qrect.width()), qreal(qrect.height())) {;}

void QQRectF::set(const QSizeF size, const QPointF center)
{
    setRect(center.x() - size.width()  / 2,
            center.y() - size.height() / 2,
            size.height(), size.width());
}

bool QQRectF::isUnit() const
{
    return (x() >= -1.0 && x() < +1.0)
            && (x() >= -1.0 && x() < +1.0)
            && (width() < 1.0) && (height() < 1.0);
}

qreal QQRectF::area() const
{
    return height() * width();
}

