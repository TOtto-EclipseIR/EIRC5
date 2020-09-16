#include "Real.h"

#include <eirXfr/Debug.h>

Real::Real() : mReal(qQNaN()), mEpsilon(1E-9) {;}

Real::Real(const double real, const double epsilon) : mReal(real), mEpsilon(epsilon) {;}

double Real::real() const
{
    return mReal;
}

bool Real::isLessThan(const double other) const
{
#ifdef QT_DEBUG
    double adjusted = other - mEpsilon;
    bool less = mReal < adjusted;
    TRACEQFI << mReal << mEpsilon << other << adjusted << less;
    return less;
#else
    return mReal < (other - mEpsilon);
#endif
}

bool Real::isZero() const
{
#ifdef QT_DEBUG
    double absReal = std::abs(mReal);
    bool zero = absReal < mEpsilon;
    return zero;
#else
    return std::abs(mReal) < mEpsilon;
#endif
}

Real::operator double() const
{
    return real();
}
