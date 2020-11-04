// file: {EIRC2 repo)./src/libs/eirType/QQRectList.cpp
#include "QQRectList.h"

void QQRectList::set(const QList<QQRect> &rects)
{
    QList<QQRect>::clear();
    QList<QQRect>::append(rects);
}

qreal QQRectList::averageOverlap() const
{
    if (isEmpty()) return qQNaN();
    QQRectList copy = *this;
    qreal accumulatedOverlap = 0.0;
    QQRect prevRect = copy.takeFirst();
    while ( ! isEmpty())
    {
        QQRect nextRect = copy.takeFirst();
        accumulatedOverlap += prevRect.overlapRatio(nextRect);
        prevRect = nextRect;
    }
    return accumulatedOverlap / size();
}

QRectVector QQRectList::vector() const
{
    QRectVector vec;
    foreach (QQRect rc, mid(0)) vec << QRect(rc);
    return vec;
}

QString QQRectList::toDebugString() const
{
    QString rtn;
    foreach (QQRect qqrc, mid(0))
        rtn += (rtn.isEmpty() ? "{" : ", {") + qqrc.toString() + "}";
    return rtn;
}

QList<QRect> QQRectList::list() const
{
    QList<QRect> list;
    foreach (QQRect qqrc, mid(0)) list << QRect(qqrc);
    return list;
}
