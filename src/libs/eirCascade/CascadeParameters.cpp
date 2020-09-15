#include "CascadeParameters.h"

#include <eirXfr/Debug.h>

CascadeParameters::CascadeParameters(const Configuration &cascadeConfig)
    : mConfig(cascadeConfig)
{
    TRACEFN;
    NEEDDO(ImageSize); NEEDDO(coreSize);
    mConfig.setName("CascadeParameters:mConfig");
    mConfig.dump();
#if 0
    NEEDDO(it);
    mAll = true;
    mFactor = 1.010;
    mNeighbors = 0;
#elif 0
    mAll = mConfig.boolean("FindAll", false);
    mFactor = parseFactor();
    mNeighbors = mConfig.unsignedInt("Neighbors", mAll ? 1 : 3);
#else
#endif
}
/*
CascadeParameters::CascadeParameters(const double factor, const int neighbors)
    : mFactor(factor), mNeighbors(neighbors) {;}
*/
void CascadeParameters::configureCascade(const Configuration &cascadeConfig)
{
    TRACEFN;
    mConfig += cascadeConfig;
    mConfig.dump();
}

void CascadeParameters::calculate(const QSize imageSize, const QSize coreSize)
{
    TRACEQFI << imageSize << coreSize;
    NEEDUSE(imageSize);
    NEEDUSE(coreSize);

    double fac = parseFactor();
    mFactor = qIsNull(fac) ? 1.160 : fac;
    NEEDDO("Default Based on Image/Core size & MaxDetectors, etc.");

    int neigh = mConfig.signedInt("Neighbors");
    mNeighbors = (neigh >= 0) ? neigh : 2;
    NEEDDO("When AllRect mode is completed, >= 1");

#if 0
    MUSTDO(RemoveForFlight);
    mFactor = 1.050;
    mNeighbors = 0;
#endif
    DUMPVAL(factor());
    DUMPVAL(neighbors());
}

double CascadeParameters::factor() const
{
    return mFactor;
}

int CascadeParameters::neighbors() const
{
    return mNeighbors;
}

int CascadeParameters::flags() const
{
    return mFlags;
}

QSize CascadeParameters::minSize() const
{
    return ! mMinSize.isValid() ? QSize(0,0) : mMinSize;
}

QSize CascadeParameters::maxSize() const
{
    return ! mMaxSize.isValid() ? QSize(0,0) : mMaxSize;
}

Configuration CascadeParameters::cascadeConfig() const
{
    return mConfig;
}

QStringList CascadeParameters::dumpList() const
{
    QStringList qsl;
    qsl << QString("%1 = %2").arg("mAll").arg(mAll);
    qsl << QString("%1 = %2").arg("factor").arg(factor());
    qsl << QString("%1 = %2").arg("mNeighbors").arg(neighbors());
    qsl << QString("%1 = %2").arg("mFlags").arg(flags());
    qsl << QString("%1 = %2x%3").arg("mMinSize").arg(minSize().width()).arg(minSize().height());
    qsl << QString("%1 = %2x%3").arg("mMaxSize").arg(maxSize().width()).arg(maxSize().height());
    return qsl;
}

void CascadeParameters::dump() const
{
    DUMP << dumpList();
}

double CascadeParameters::parseFactor()
{
    TRACEFN;
    double result=qQNaN();
    double f = mConfig.real("Factor");
    if (f < 2.000)
        result = 0.0;
    else
        result = 1.000 + f / 1000.0;
    TRACE << f << result;
    EXPECTNE(result, qQNaN());
    return result;
}

