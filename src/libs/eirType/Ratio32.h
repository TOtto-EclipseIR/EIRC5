#pragma once

#include "Rational.h"

#include <stdint.h>

class Ratio32 : public Rational
{
public:
    Ratio32();
    Ratio32(const int n);
    Ratio32(const qreal r);

private:
    static const qint32 cmDenom = INT32_MAX;
};

