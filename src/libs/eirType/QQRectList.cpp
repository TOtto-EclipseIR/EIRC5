// file: {EIRC2 repo)./src/libs/eirType/QQRectList.cpp
#include "QQRectList.h"

QQRectList::QQRectList(const QList<QQRect> rects)
{
    set(rects);
}

void QQRectList::set(const QList<QQRect> rects)
{
    QList<QQRect>::clear();
    QList<QQRect>::append(rects);
}

QVector<QRect> QQRectList::vector() const
{
    QVector<QRect> vec;
    foreach (QQRect rc, mid(0))
        vec << QRect(rc);
    return vec;
}
