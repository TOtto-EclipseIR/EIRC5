#pragma once
#include <eirQtCV.h>

#include <opencv2/core/types.hpp>

#include <QRect>

#include <vector>

#include <eirType/QQRect.h>

class EIRQTCV_EXPORT cvRect : public cv::Rect
{
public:
    typedef std::vector<cvRect> StdVector;

public:
    cvRect();
    cvRect(const QRect qrc);
    cvRect(const cv::Rect cvrc);
    cvRect(const QQRect qqrc);
    cvRect(const int left, const int top, const int width, const int height);
    QQRect toRect() const;
};

