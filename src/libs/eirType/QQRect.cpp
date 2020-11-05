// file: {EIRC2 repo)./src/libs/eirType/QQRect.cpp
#include "QQRect.h"

#include <QtMath>

#include <eirXfr/Debug.h>

#include "QQPoint.h"
#include "QQRectF.h"

QQRect::QQRect() {;}
QQRect::QQRect(const QRect rc) : mSize(rc.size()), mCenter(rc.center()) {;}
QQRect::QQRect(int width, int height, int left, int top)
    : mSize(width, height), mCenter(left + width / 2, top + height / 2) {;}
QQRect::QQRect(const QQSize size, const QPoint center) : mSize(size), mCenter(center) {;}
QQRect::QQRect(const QQSize size) : mSize(size), mCenter(0, 0) {;}
QQRect::QQRect(const QRectF rcf) { set(rcf); }

QQRect::operator QRect() const

{
    return QRect(left(), top(), width(), height());
}

QRectF QQRect::toRectF() const
{
    return QRectF(left(), top(), width(), height());
}

bool QQRect::operator ==(const QQRect &other)
{
    return size() == other.size() && center() == other.center();
}

bool QQRect::isValid() const
{
    return left() < right() && top() < bottom();
}

bool QQRect::contains(const int x, const int y) const
{
    return left() <= x && x <= right() && top() <= y && y <= bottom();
}

bool QQRect::contains(const QQRect other) const
{
    return contains(other.left(), other.top())
            && contains(other.right(), other.bottom());
}

bool QQRect::intersects(const QQRect &other) const
{
    return QRect(*this).intersects(QRect(other));
}

QQRect QQRect::intersected(const QQRect &other) const
{
    return QRect(*this).intersected(QRect(other));
}

QQRect QQRect::set(const QRectF rcf)
{
    QQRect rc(qRound(rcf.width()), qRound(rcf.height()),
              qRound(rcf.x()), qRound(rcf.y()));
    return rc;
}

void QQRect::set(const QSize size, const QPoint center)
{
    mSize = size, mCenter = center;
}

QQRect QQRect::squaredByMaxDimension() const
{
    int maxdim = qMax(width(), height());
    return QQRect(QQSize(maxdim, maxdim), center());
}

void QQRect::squareByMaxDimension()
{
    *this = squaredByMaxDimension();
}

QQRect QQRect::united(const QQRect other)
{
    QQRect rtn;
    int l = qMin(left(),  other.left());
    int t = qMin(top(),  other.top());
    int r = qMin(right(),  other.right());
    int b = qMin(bottom(),  other.bottom());
    QQPoint c((l + r) / 2, (t + b) / 2);
    QQSize s(r - l, b - t);
    return QQRect(s, c);
}
#if 0
void QQRect::square(const bool byArea)
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
#endif
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
#if 0
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
#endif
#if 1
qreal QQRect::overlapRatio(const QQRect other) const
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
#endif
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

QDebug operator<<(QDebug dbg, const QQRect &rc)
{
    dbg << rc.toString();
    return dbg;
}

uint qHash(const QQRect &rc, uint seed) noexcept
{
    QtPrivate::QHashCombine hash;
    seed = hash(seed, rc.width());
    seed = hash(seed, rc.height());
    seed = hash(seed, rc.center().x());
    seed = hash(seed, rc.center().y());
    return seed;
}

