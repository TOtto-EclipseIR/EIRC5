#pragma once

#include <QSize>

#include <opencv2/core/types.hpp>

class cvSize
{
public:
    cvSize();
    cvSize(const QSize &qsize);
    cvSize(const int cols, const int rows);
    cvSize(const cv::Size &other);
    operator QSize () const;
    int rows() const;
    int cols() const;
    cv::Size size() const;
    operator cv::Size() const;
    bool isEmpty() const;


private:
    cv::Size mCvSize;
};

