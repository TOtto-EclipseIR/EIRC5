#pragma once
#include <eirQtCV.h>

#include <vector>

#include <opencv2/core/types.hpp>

#include <eirType/QQRectList.h>

class EIRQTCV_EXPORT cvRectVector : public std::vector<cv::Rect>
{
public:
    cvRectVector();
    QQRectList toRectList() const;
};

