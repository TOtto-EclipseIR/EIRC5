#pragma once
#include "eirQtCV.h"

#include <eirType/BasicName.h>
#include <eirExe/ConfigObject.h>

#include "cvCascade.h"
#include "cvMat.h"
#include "qtcvSize.h"

class EIRQTCV_EXPORT CascadeParameters
{
public:
    CascadeParameters(const cvCascade &cascade);
    double factor() const;
    int neighbors() const;
    int flags() const;
    qtcvSize minSize() const;
    qtcvSize maxSize() const;
    Configuration cascadeConfig() const;

private:
    double calcFactor(); // non-const

private:
    CascadeType mCascadeType;
    const ConfigObject *cmpCfgObj=nullptr;
    const cvCascade cmCascade;
    Configuration mConfig;
    bool mAll=false;
    double mFactor=1.100;
    int mNeighbors=0;
    int mFlags=0;
    qtcvSize mMinSize;
    qtcvSize mMaxSize;
};

