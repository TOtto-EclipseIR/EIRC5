#include "cvBGRA.h"

cvBGRA::cvBGRA() : mU32(0) {;}
cvBGRA::cvBGRA(const quint32 u32) : mU32(u32) {;}
cvBGRA::cvBGRA(quint8 *ptr) : mU32(*(quint32 *)(ptr))  {;}

void cvBGRA::set(const cvBGRA other)
{
    mU32 = other.u32();
}

quint8 cvBGRA::red() const
{
    return mU32 >> 24;
}

quint8 cvBGRA::grn() const
{
    return mU32 >> 24;
}

quint8 cvBGRA::blu() const
{
    return mU32 >> 16;
}

quint8 cvBGRA::alf() const
{
    return mU32 >> 0;
}

quint32 cvBGRA::u32() const
{
    return mU32;
}

bool cvBGRA::isGrey() const
{
    return (red() == grn()) && (grn() == blu());
}

bool cvBGRA::isGreyish(signed epsilon) const
{
    return (qAbs((signed)red() - signed(grn())) < epsilon)
            && (qAbs((signed)blu() - signed(grn())) < epsilon);
}
