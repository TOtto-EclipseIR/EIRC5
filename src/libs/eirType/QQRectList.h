// file: {EIRC2 repo)./src/libs/eirType/QQRectList.h
#pragma once
#include "eirType.h"

#include <QList>
#include "QQRect.h"

#include <QMetaType>
#include <QRect>
#include <QVariant>
#include <QVector>

#include <eirBase/Typedefs.h>
#include <eirXfr/XerReturn.h>

class EIRTYPE_EXPORT QQRectList : public QList<QQRect>
{
public:
    QQRectList(const QList<QQRect> rects=QList<QQRect>()) : QList<QQRect>(rects) {;}
    bool notEmpty() const                   { return ! isEmpty(); }
    void set(const QList<QQRect> &rects);
    void set(const QVariant &variant)       { set(variant.value<QQRectList>()); }
    qreal averageOverlap() const;
    QList<QRect> list() const;
    QRectVector vector() const;
    QVariant toVariant() const              { return QVariant::fromValue(*this); }
    operator QVariant() const               { return toVariant(); }
    QString toDebugString() const;
};
Q_DECLARE_METATYPE(QQRectList);

