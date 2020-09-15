#pragma once
#include "eirCascade.h"

#include <QSize>
#include <QStringList>

#include <eirType/BasicName.h>
#include <eirExe/ConfigObject.h>

#include "CascadeType.h"

class EIRCASCADE_EXPORT CascadeParameters
{
public:
    CascadeParameters(const Configuration &cascadeConfig=Configuration());
    //CascadeParameters(const double factor, const int neighbors);
    void configureCascade(const Configuration &cascadeConfig);
    void calculate(const QSize imageSize, const QSize coreSize);
    double factor() const;
    int neighbors() const;
    int flags() const;
    QSize minSize() const;
    QSize maxSize() const;
    Configuration cascadeConfig() const;
    QStringList dumpList() const;
    void dump() const;

private:
    double parseFactor(); // non-const

private:
    CascadeType mCascadeType;
    Configuration mConfig;
    bool mAll=false;
    double mFactor=1.100;
    int mNeighbors=0;
    int mFlags=0;
    QSize mMinSize;
    QSize mMaxSize;
};

