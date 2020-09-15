#pragma once
#include "eirType.h"

#include <QRectF>

#include <QList>
#include <QPoint>
#include <QSize>


class EIRTYPE_EXPORT QQRectF : public QRectF
{
public:
    typedef QList<QQRectF> List;
public:
    QQRectF();
    QQRectF(qreal x, qreal y, qreal width, qreal height);
    QQRectF(const QSizeF size, const QPointF center);
    QQRectF(const QRect qrect);
    void set(const QSizeF size, const QPointF center);
    bool isUnit() const;
    qreal area() const;
};

