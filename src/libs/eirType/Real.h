#pragma once
#include "eirType.h"

class EIRTYPE_EXPORT Real
{
public:
    Real();
    Real(const double real, const double epsilon=1E-5);
    double real() const;
    bool isZero() const;
    bool isLessThan(const double other) const;
    operator double() const;

private:
    double mReal;
    double mEpsilon;
};

