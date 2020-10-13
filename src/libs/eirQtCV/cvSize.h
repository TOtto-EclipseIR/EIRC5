#pragma once
#include "eirQtCV.h"

#include <opencv2/core/types.hpp>

#include <QtDebug>
#include <QSize>

#include <vector>

#include <eirType/QQSize.h>

class EIRQTCV_EXPORT cvSize : public cv::Size
{
public:
    typedef std::vector<cvSize> Vector;

public:
    cvSize();
    cvSize(const QSize qsz);
    cvSize(const cv::Size other);
    cvSize(const int w, const int h);
    void nullify();
    void set(const QSize qsz);
    void set(const int w, const int h);
    void set(const cv::Size cvsz);
    QQSize toSize() const;
    bool isValid() const;
    QString toDebugString() const;

private:
};

EIRQTCV_EXPORT QDebug operator<<(QDebug dbg, const cvSize &cvsz);
