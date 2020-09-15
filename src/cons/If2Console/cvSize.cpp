#include "cvSize.h"

cvSize::cvSize() {;}

cvSize::cvSize(const QSize &qsize)
    : mCvSize(qsize.width(), qsize.height()) {;}

cvSize::cvSize(const int cols, const int rows)
    : mCvSize(cols, rows) {;}

cvSize::cvSize(const cv::Size &other)
    : mCvSize(other) {;}

cvSize::operator QSize() const
{
    return QSize(mCvSize.width, mCvSize.height);
}

cvSize::operator cv::Size() const
{
    return mCvSize;
}

bool cvSize::isEmpty() const
{
    return mCvSize.empty();
}
