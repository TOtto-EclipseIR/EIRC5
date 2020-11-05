#include "Rational.h"

#include <QtDebug>

Rational::Rational() : mNumerator(0), mDenominator(0) {;}
Rational::Rational(const Rational::Pair p) : mNumerator(p.first), mDenominator(p.second) {;}
Rational::Rational(const int n) : mNumerator(n), mDenominator(1) {;}
Rational::Rational(const int n, const int d) : mNumerator(n), mDenominator(d) {;}
Rational::Rational(const qreal r, const int d) : mNumerator(r*d), mDenominator(d) {;}

qreal Rational::toReal() const
{
    return isNull() ? qQNaN() : qreal(mNumerator) / qreal(mDenominator);
}

void Rational::set(const int n, const int d)
{
    mNumerator = n, mDenominator = d;
}

QString Rational::toString() const
{
    return QString("%1 / %2 = %3").arg(numerator()).arg(denominator()).arg(toReal());
}

QDebug operator<<(QDebug dbg, const Rational &r)
{
    dbg << r.toString();
    return dbg;
}


