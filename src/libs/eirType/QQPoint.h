#pragma once
#include "eirType.h"

#include <QPoint>

#include "QQSize.h"

class EIRTYPE_EXPORT QQPoint : public QPoint
{
public:
    QQPoint() {;}
    QQPoint(const QPoint other) : QPoint(other) {;}
    QQPoint(const int x, const int y) : QPoint(x, y) {;}
    QQPoint(const int index, const QQSize size)
        : QPoint(index % size.width(), index / size.width()) {;}
};

