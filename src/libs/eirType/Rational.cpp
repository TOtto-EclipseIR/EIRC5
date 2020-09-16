#include "Rational.h"

Rational::Rational() : mNumerator(0), mDenominator(0) {;}
Rational::Rational(const Rational::Pair p) : mNumerator(p.first), mDenominator(p.second) {;}
Rational::Rational(const int n) : mNumerator(n), mDenominator(1) {;}
Rational::Rational(const int n, const int d) : mNumerator(n), mDenominator(d) {;}
Rational::Rational(const qreal r, const int d) : mNumerator(r*d), mDenominator(d) {;}

qreal Rational::toReal() const
{
    return qreal(mNumerator) / qreal(mDenominator);
}


