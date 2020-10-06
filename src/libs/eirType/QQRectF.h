#pragma once
#include "eirType.h"

#include <QRectF>

#include <QList>
#include <QMetaType>
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
    QQRectF divide(const qreal divisor);
    QQRectF operator / (const qreal divisor);
    QString toString() const;
    operator QString () const;
};
Q_DECLARE_METATYPE(QQRectF);

EIRTYPE_EXPORT QDebug operator<<(QDebug dbg, const QQRectF &rcf);
