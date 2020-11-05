#pragma once// file: {EIRC2 repo)./src/libs/eirType/QQRect.h
#include "eirType.h"


#include <QList>
#include <QMetaType>
#include <QPoint>
#include <QRect>
#include <QSize>

#include "QQPoint.h"
#include "QQSize.h"

class EIRTYPE_EXPORT QQRect
{
public:
    QQRect();
    QQRect(const QRect rc);
    QQRect(int width, int height, int left, int top);
    QQRect(const QQSize size, const QPoint center);
    QQRect(const QQSize size);
    QQRect(const QRectF rcf);
    operator QRect() const;
    QRectF toRectF() const;
    bool operator == (const QQRect &other);
    bool isValid() const;
    bool contains(const int x, const int y) const;
    bool contains(const QQRect other) const;
    bool intersects(const QQRect &other) const;
    QQRect intersected(const QQRect &other) const;
    QQSize size() const             { return mSize; }
    QQPoint center() const          { return mCenter; }
    int width() const               { return size().width(); }
    int height() const              { return size().height(); }
    int left() const                { return mCenter.x() - width() / 2; }
    int top() const                 { return mCenter.y() - height() / 2; }
    int right() const               { return mCenter.x() + width() / 2; }
    int bottom() const              { return mCenter.y() + height() / 2; }
    QQRect set(const QRectF rcf);
    void set(const QSize size, const QPoint center);
    QQRect squaredByArea() const;
    QQRect squaredByMaxDimension() const;
    void squaredByArea();
    void squareByMaxDimension();
    QQRect united(const QQRect other);
    void unite(const QQRect other);
    int area() const;
    QQRect overlapped(const QQRect other) const;
    qreal overlapRatio(const QQRect other) const;
    QQRect expandedBy(const qreal factor) const;
    QQRect operator * (const qreal factor) const;
    QString toString() const;

private:
    QQSize mSize;
    QQPoint mCenter;
};
Q_DECLARE_METATYPE(QQRect);
EIRTYPE_EXPORT uint qHash(const QQRect &rc, uint seed = 0) noexcept;
EIRTYPE_EXPORT QDebug operator<<(QDebug dbg, const QQRect &rc);

