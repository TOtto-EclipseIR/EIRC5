#pragma once
#include "eirType.h"

#include <QPoint>

#include "QQSize.h"

class EIRTYPE_EXPORT QQPoint : public QPoint
{
public:
    QQPoint();
    QQPoint(const int x, const int y);
    QQPoint(const int index, const QQSize size);
};

