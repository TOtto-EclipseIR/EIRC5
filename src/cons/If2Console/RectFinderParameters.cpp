#include "RectFinderParameters.h"

#include <eirXfr/Debug.h>
#include <eirExe/ConfigObject.h>

#include "cvSize.h"

RectFinderParameters::RectFinderParameters()
{
    TRACEFN;
}

void RectFinderParameters::configure(const QSize &coreSize,
                                     const Configuration &config)
{
    mConfig = config;
    mCoreSize = coreSize;
}

void RectFinderParameters::calculate(const QSize &imageSize, const QRect &regionRect)
{
    TRACEQFI << imageSize << regionRect;
    NEEDDO(aspect);
    WANTUSE(regionRect);
    int imageMinDimension = qMin(imageSize.width(),
                         imageSize.height());
    int cfgMinWidth = mConfig.signedInt("MinWidth");
    int cfgMaxWidth = mConfig.signedInt("MaxWidth");
    int imageMaxWidth
            = ((0 == cfgMaxWidth)
             || (cfgMaxWidth > imageMinDimension))
                ? imageMinDimension
                : cfgMaxWidth;
    int imageMinWidth
            = (cfgMinWidth < mCoreSize.width())
                ? mCoreSize.width()
                : cfgMinWidth;
    mCvMinSize = cvSize(imageMinWidth, imageMinWidth);
    mCvMaxSize = cvSize(imageMaxWidth,
                        imageMaxWidth);

    int cfgFactor = mConfig.signedInt("Factor");
    mScaleFactor = (cfgFactor < 1)
            ? 1.125 : (1.0 + qreal(cfgFactor) / 1000.0);
}

void RectFinderParameters::setSize(const QSize minSize,
                                   const QSize maxSize)
{
    mMinSize = minSize, mMaxSize = maxSize;
}

void RectFinderParameters::setFactor(const qreal factor)
{
    mScaleFactor = factor;
}

void RectFinderParameters::setNeighbors(const int neighbors)
{
    mMinNeighbors = neighbors;
}

double RectFinderParameters::scaleFactor() const
{
    return  mScaleFactor;
}

int RectFinderParameters::minNeighbors() const
{
    return  mMinNeighbors;
}

int RectFinderParameters::flags() const
{
    WEXPECTEQ(0, mFlags);
    return mFlags;
}

cvSize RectFinderParameters::minSize() const
{
    return cvSize(mMinSize);
}

cvSize RectFinderParameters::maxSize() const
{
    return mMaxSize;
}

int RectFinderParameters::minDimension(const QSize imageSize) const
{
    NEEDUSE(imageSize);
    return mMinDimension;
}

int RectFinderParameters::minWidth(const QSize imageSize) const
{
    NEEDUSE(imageSize);
    return mMinWidth;
}

int RectFinderParameters::maxWidth(const QSize imageSize) const
{
    NEEDUSE(imageSize);
    return mMaxWidth;
}
