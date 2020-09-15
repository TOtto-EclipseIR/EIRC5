// file: {EIRC2 repo)./src/libs/eirType/QQRect.cpp
#include "QQRect.h"

#include <eirXfr/Debug.h>
//#include "../../libs/eirType/Debug.h"

#include "QQRectF.h"

QQRect::QQRect() {;}

QQRect::QQRect(int x, int y, int width, int height)
    : QRect(x, y, width, height) {;}

QQRect::QQRect(const QSize size, const QPoint center)
    : QRect(center.x() - size.width()  / 2,
            center.y() - size.height() / 2,
            size.height(), size.width()) {;}

QQRect::QQRect(const QRectF rcf) { set(rcf); }

QQRect QQRect::set(const QRectF rcf)
{
    QQRect rc(qRound(rcf.x()), qRound(rcf.y()),
              qRound(rcf.width()), qRound(rcf.width()));
    return rc;
}

void QQRect::set(const QSize size, const QPoint center)
{
    setRect(center.x() - size.width()  / 2,
            center.y() - size.height() / 2,
            size.height(), size.width());
}

int QQRect::area() const
{
    return height() * width();
}

qreal QQRect::overlap(const QQRect other)
{
    QRect intersection = intersected(other);
/*
    TRACEQFI  << *this << area()
              << intersection << QQRect(intersection).area()
              << other << other.area()
              << QQRectF(intersection).area() / qreal(area());
*/
    return QQRectF(intersection).area() / qreal(area());
}

QQRect QQRect::expandedBy(const qreal factor) const
{
    WANTDO(TrimmedToSize);
    QSizeF szf = QSizeF(size());
    QQRect expanded(QSize(qRound(szf.width() * factor),
                          qRound(szf.height() * factor)),
                    center());
    return expanded;
}

QQRect QQRect::operator *(const qreal factor) const
{
    return  expandedBy(factor);
}

