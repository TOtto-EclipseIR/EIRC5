#include "Ratio32.h"

Ratio32::Ratio32() {;}
Ratio32::Ratio32(const int n) : Rational(n, cmDenom) {;}
Ratio32::Ratio32(const qreal r) : Rational(r, cmDenom) {;}
