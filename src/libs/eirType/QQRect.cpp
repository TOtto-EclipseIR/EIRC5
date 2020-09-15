// file: {EIRC2 repo)./src/libs/eirType/QQRect.cpp
#include "QQRect.h"

#include <QtMath>

#include <eirXfr/Debug.h>
//#include "../../libs/eirType/Debug.h"

#include "QQRectF.h"

QQRect::QQRect() {;}

QQRect::QQRect(int x, int y, int width, int height)
    : QRect(x, y, width, height) {;}

QQRect::QQRect(const QSize size, const QPoint center)
    : QRect(QPoint(center.x() - size.width()  / 2,
                   center.y() - size.height() / 2),
            size) {;}

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

void QQRect::makeSquare()
{
    int d = qRound(qSqrt(area()));
    set(QSize(d,d), center());
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
#if 1
    rt = qMax(t, ot), rb = qMin(b, ob);
    rl = qMax(l, ol), rr = qMin(r, ox);
#else
    if (contains(l, ol, r))
        if (contains(l, ox, r))
            rl = l, rr = r; // o left-right is inside this
        else
            rl = l, rr = ox; // o left is inside, o right isn't
    else if (contains(ol, l, ox))
        if (contains(ol, r, ox))
            rl = ol, rr = ox; // this left-right is inside other
        else
            rl = ol, rr = r; // this l inside, this r not
    else
        return QQRect(); // no left-right overlap

    if (contains(t, ot, b))
        if (contains(t, ob, b))
            rt = t, rb = b; // o top-bottom is inside this
        else
            rt = t, rr = ob; // o top is inside, o bottom isn't
    else if (contains(ot, t, ob))
        if (contains(ot, b, ob))
            rt = ot, rb = ob; // this top-bottom is inside other
        else
            rt = ot, rb = b; // this t inside, this b not
    else
        return QQRect(); // no top-bottom overlap
#endif
    QQRect rc(rl, rt, rr-rl, rb-rt);
    TRACE << rc;
    EXPECT(rc.isValid());
    return rc;
}

qreal QQRect::overlap(const QQRect other) const
{
    EXPECT(isValid());
    if ( ! isValid()) return 0.0;
    QQRect intersection = overlapped(other);
    TRACEQFI  << toString() << area()
              << intersection << intersection.area()
              << other << other.area()
              << QQRectF(intersection).area() / qreal(area());
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
