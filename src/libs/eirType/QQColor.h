#pragma once
#include "eirType.h"

#include <QColor>

#include <QVector>

#include "Rational.h"

class EIRTYPE_EXPORT QQColor : public QColor
{
public:
    typedef QVector<QQColor> Vector;

public:
    QQColor();
    QQColor(const QColor other);
    QQColor(const QRgb rgb);
    QQColor(const int r, const int g, const int b, const int a=255);
    QQColor(const QString &namedColor);
    QQColor(const char *namedColor);
    QQColor(const QColor::Spec spec, const int i1=0, const int i2=0,
                                     const int i3=0, const int i4=0);
    QQColor(const QColor::Spec spec, const qreal f1=0.0, const qreal f2=0.0,
                                     const qreal f3=0.0, const qreal f4=0.0);
    QQColor(const QColor::Spec spec, const Rational f1=Rational(), const Rational f2=Rational(),
                                     const Rational f3=Rational(), const Rational f4=Rational());
    void nullify();
    bool isNull() const;
    bool isValid() const;
    bool notValid() const;
    bool isValidGamut() const;
    QString toString() const;
    QString toSpecString() const;


private:
    static bool isValid(const quint8 u);
    static bool isValid(const qreal u);
};

EIRTYPE_EXPORT QDebug operator<<(QDebug dbg, const QQColor &item);
