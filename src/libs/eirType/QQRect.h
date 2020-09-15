#pragma once// file: {EIRC2 repo)./src/libs/eirType/QQRect.h
#include "eirType.h"

#include <QRect>

#include <QList>
#include <QMetaType>
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
    void makeSquare();
    int area() const;
    QQRect overlapped(const QQRect other) const;
    qreal overlap(const QQRect other) const;
    QQRect expandedBy(const qreal factor) const;
    QQRect operator * (const qreal factor) const;
    QString toString() const;
    operator QString () const;
};
Q_DECLARE_METATYPE(QQRect);

EIRTYPE_EXPORT QDebug operator<<(QDebug dbg, const QQRect &rc);

