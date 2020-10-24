// file: {EIRC2 repo)./src/libs/eirType/QQRect.cpp
#include "QQRect.h"

#include <QtMath>

#include <eirXfr/Debug.h>

#include "QQPoint.h"
#include "QQRectF.h"

QQRect::QQRect() {;}
QQRect::QQRect(const QRect rc) : QRect(rc) {;}
QQRect::QQRect(int x, int y, int width, int height)
    : QRect(x, y, width, height) {;}
QQRect::QQRect(const QSize size, const QPoint center)
    : QRect(QPoint(center.x() - size.width()  / 2,
                   center.y() - size.height() / 2), size) {;}
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

void QQRect::makeSquare(const bool byArea)
{
    if (byArea)
    {
        int d = qRound(qSqrt(area()));
        set(QSize(d,d), center());
    }
    else
    {
        int w = width(), h = height();
        if (w == h) return;                                 /* /=======\ */
        QQPoint c = center();
        int m = qMax(w, h);
        set(QQSize(m, m), c);
    }
}

void QQRect::unite(const QQRect other)
{
    *this = united(other);
}

int QQRect::area() const
{
    return height() * width();
}

inline int contains(const int lo, const int v, const int hi)
{ return lo <= v && v <= hi; }

QQRect QQRect::overlapped(const QQRect other) const
{
    TRACEQFI << toString() << other.toString() << intersects(other);
    if ( ! intersects(other)) return QQRect();

    int t = top(),      ot = other.top(),       rt = 0;
    int l = left(),     ol = other.left(),      rl = 0;
    int b = bottom(),   ob = other.bottom(),    rb = 0;
    int r = right(),    ox = other.right(),     rr = 0;
    rt = qMax(t, ot), rb = qMin(b, ob);
    rl = qMax(l, ol), rr = qMin(r, ox);
    QQRect rc(rl, rt, rr-rl, rb-rt);
    TRACE << rc;
    EXPECT(rc.isValid());
    return rc;
}

qreal QQRect::overlap(const QQRect other) const
{
    TRACEQFI << other << toString();
    EXPECT(isValid());
    EXPECT(other.isValid());
    if ( ! isValid() || ! other.isValid()) return qQNaN();  /* /========\ */
    if (contains(other)) return 1.0;                        /* /========\ */
    if (other.contains(*this)) return 1.0;                  /* /========\ */
    if ( ! intersects(other)) return 0.0;                   /* /========\ */

    QQRect intersection = intersected(other);
    qreal intArea = intersection.area();
    qreal minArea = qMin(area(), other.area());
    TRACE << intersection << intArea << minArea << intArea / minArea;
    return intArea / minArea;
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

QString QQRect::toString() const
{
    return QString("(%1x%2) @%3,%4")
               .arg(width()).arg(height())
               .arg(center().x()).arg(center().y());
}

QQRect::operator QString() const
{
    return toString();
}



QDebug operator<<(QDebug dbg, const QQRect &rc)
{
    dbg << rc.toString();
    return dbg;
}
