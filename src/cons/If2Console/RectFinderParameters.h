#pragma once

#include <QRect>
#include <QSize>
#include <QVariantMap>

#include <opencv2/core.hpp>
#include <opencv2/core/core.hpp>

#include <eirExe/ConfigObject.h>

#include "cvSize.h"
//#include "RectFinder.h"

class RectFinderParameters
{
public:
    RectFinderParameters();
    void configure(const QSize &coreSize,
                   const Configuration &config);
    void calculate(const QSize &imageSize,
                   const QRect &regionRect=QRect());
    void setSize(const QSize minSize,
                 const QSize maxSize);
    void setSize(const int minWidth,
                 const int maxWidth);
    void setFactor(const qreal factor);
    void setNeighbors(const int neighbors);

    // access
    double scaleFactor() const;
    int minNeighbors() const;
    int flags() const;
    cvSize minSize() const;
    cvSize maxSize() const;

protected:
    int minDimension(const QSize imageSize) const;
    int minWidth(const QSize imageSize) const;
    int maxWidth(const QSize imageSize) const;

private:
    Configuration mConfig;
    QSize mCoreSize;

    // our intermediate values
    int mMinDimension;
    int mMinWidth;
    int mMaxWidth;
    QSize mMinSize;
    QSize mMaxSize;

    // arguments to detectMultiScale()
    qreal mScaleFactor=1.1;
    int mMinNeighbors=0;
    int mFlags=0; // per OpenCV doxy 4.2.0, no longer used
    cvSize mCvMinSize;
    cvSize mCvMaxSize;
};

