#pragma once
#include "eirType.h"

class EIRTYPE_EXPORT RealMath
{
public:
    struct Constants
    {
        constexpr static qreal EULER =             2.71828182845904523536;
        constexpr static qreal LOG2E =         1.44269504088896340736;
        constexpr static qreal LOG10E =        0.434294481903251827651;
        constexpr static qreal LN2 =           0.693147180559945309417;
        constexpr static qreal LN10 =          2.30258509299404568402;
        constexpr static qreal PI =            3.14159265358979323846;
        constexpr static qreal TWO_PI =        6.28318530718;
        constexpr static qreal TAU =           6.28318530718;
        constexpr static qreal PI_2 =          1.57079632679489661923;
        constexpr static qreal PI_4 =          0.785398163397448309616;
        constexpr static qreal PI_1_PI =       0.318309886183790671538;
        constexpr static qreal PI_2_PI =       0.636619772367581343076;
        constexpr static qreal PI_2_SQRTPI =   1.12837916709551257390;
        constexpr static qreal SQRT2 =         1.41421356237309504880;
        constexpr static qreal SQRT1_2 =       0.707106781186547524401;
    };
public:
    RealMath();
};

