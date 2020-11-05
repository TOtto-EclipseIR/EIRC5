#pragma once
#include "eirObjDet.h"

#include <eirType/Enumeration.h>
#define OBJDETENUM_ENUM(NV) \
    NV(Null, = 0)  \
    NV(GroupByBefore, ) \
    NV(GroupUnion, )   \
    NV(GroupOverlap, )   \
    NV(GroupByAfter, ) \

class EIROBJDET_EXPORT ObjDetEnum : public Enumeration
{
    DECLARE_ENUMERATION(ObjDetEnum, OBJDETENUM_ENUM)
};
