#pragma once
#include "eirObjDet.h"

#include <eirType/QQRectList.h>

class EIROBJDET_EXPORT PreScanResult
{
public:
    PreScanResult();
    QQRect result() const           { return mResultRect; }
    QQRectList included() const     { return mIncludedRects; }

public:
    QQRect mResultRect;
    QQRectList mIncludedRects;
};

