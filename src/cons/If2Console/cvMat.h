//! \file cvMat.h
#pragma once

#include <QFileInfo>
#include <QImage>

#include <QImage>
#include <QIODevice>

#include <opencv2/core/mat.hpp>

class cvMat
{
public:
    typedef cv::InputArray InputArray;

public:
    cvMat();
    cv::Mat mat() const;    bool isEmpty() const;

    cv::Mat cvtGrey() const;
    bool loaded() const;
    bool load(const QString &fileName);
    bool save(const QString &fileName);
    void set(const QImage &qimage);
    void set(const cv::Mat &other);
    QImage toImage(const QImage::Format qFormat=QImage::Format_ARGB32,
                   const QByteArray &mimeFormat="JPG");
    bool fromImage(const QImage &qImage);
    int cols() const;
    int rows() const;

protected:

    cv::Mat cvtColor(const int code) const;

private:
    cv::Mat mCvMat;
};

