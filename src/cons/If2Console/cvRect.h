#pragma once

#include <QPoint>
#include <QRect>
#include <QSize>

#include <opencv2/core/types.hpp>

#include <eirType/QQRect.h>

class cvRect
{
public:
    typedef std::vector<cvRect> Vector;

public:
    cvRect();
    cvRect(const QRect qrect);
    cvRect(const QQRect qqrect);
    cvRect(const cv::Rect &other);
    cvRect(const int left,  const int top,
           const int right, const int bottom);
    cvRect(const QPoint topLeft, const QSize size);
    cvRect(const QSize size, const QPoint center);
    void set(const cv::Point topLeft,
             const cv::Size size);
    int left() const;
    int top() const;
    int rows() const;
    int cols() const;
    bool isEmpty() const;
    QRect toQRect() const;
    operator QRect () const;

private:
    cv::Rect mCvRect;
};

