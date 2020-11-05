#pragma once
#include "eirType.h"

#include <QPair>

class EIRTYPE_EXPORT Rational
{
    typedef  QPair<int, int> Pair;

public:
    Rational();
    Rational(const Pair p);
    Rational(const int n);
    Rational(const int n, const int d);
    Rational(const qreal r, const int d);
    bool isNull() const             { return 0 == denominator(); }
    bool isUnit(const bool formal=true) const;
    bool isValid() const;
    bool isZero() const;
    bool isNegative() const;
    qreal toReal() const;
    float toFloat() const;
    double toDouble() const;
    int numerator() const           { return mNumerator; }
    int denominator() const         { return mDenominator; }
    operator qreal () const         { return toReal(); }
    void set(const int n, const int d);
    void nullify();
    void unitify(const bool byModulo=false);
    QString toString() const;


private:
    int mNumerator=0;
    int mDenominator=0;

};

EIRTYPE_EXPORT QDebug operator<<(QDebug dbg, const Rational &item);
