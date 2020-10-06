#pragma once// file: {EIRC2 repo)./src/libs/eirType/QQRect.h
#include "eirType.h"

#include <QRect>

#include <QList>
#include <QPoint>
#include <QSize>


class EIRTYPE_EXPORT QQRect : public QRect
{
public:
    typedef QList<QQRect> List;
public:
    QQRect();
    QQRect(int x, int y, int width, int height);
    QQRect(const QSize size, const QPoint center);
    QQRect(const QRectF rcf);
    QQRect set(const QRectF rcf);
    void set(const QSize size, const QPoint center);
    int area() const;
    qreal overlap(const QQRect other);
    QQRect expandedBy(const qreal factor) const;
    QQRect operator * (const qreal factor) const;
};

