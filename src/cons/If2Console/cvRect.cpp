#include "cvRect.h"

cvRect::cvRect() {;}

cvRect::cvRect(const cv::Rect &other)
{
    set(other.tl(), other.size());
}

void cvRect::set(const cv::Point topLeft,
                 const cv::Size size)
{
    mCvRect = cv::Rect(topLeft, size);
}

QRect cvRect::toQRect() const
{
    return QRect(mCvRect.x,     mCvRect.y,
                 mCvRect.width, mCvRect.height);
}

cvRect::operator QRect() const
{
    return toQRect();
}
