// file: {EIRC2 repo)./src/libs/eirType/QQRectList.h
#pragma once
#include "eirType.h"

#include <QList>
#include "QQRect.h"

#include <QRect>
#include <QVector>

class EIRTYPE_EXPORT QQRectList : public QList<QQRect>
{
public:
    QQRectList(const QList<QQRect> rects=QList<QQRect>());
    void set(const QList<QQRect> rects);
    QVector<QRect> vector() const;
};

