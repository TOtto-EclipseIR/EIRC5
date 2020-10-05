#pragma once
#include "eirQtCV.h"

#include <QFileInfo>
#include <QImage>
#include <QPixmap>
#include <QVector>

#include <eirType/QQImage.h>

namespace cv { class Mat; }
typedef QVector<int> IntVector;

class EIRQTCV_EXPORT cvMat
{
public:
    cvMat();
    cvMat(const int cols, const int rows, const int type);
    cvMat(cv::Mat &otherMat);
    ~cvMat();
    void clear();
    cv::Mat mat() const;
    cv::Mat mat();
    cv::Mat operator()() const;
    size_t totalPixels() const;
    size_t depthInBytes() const;
    int depth() const;
    int stride() const;
    bool isContinuous() const;
    qsizetype sizeInBytes() const;
    size_t bytesPerLine() const;
    void *data() const;
    const quint8 *ptr(const int row) const;
    quint8 *ptr(const int row);
    int cols() const;
    int rows() const;
    int type() const;
    bool isNull() const;
    bool isEmpty() const;
    QSize size() const;
    void set(cv::Mat *other);
    QQImage toGreyImage() const;
    QImage::Format qformat() const;
    QString toDebugString() const;

public: // static
    static cvMat greyFromImage(const QQImage &image);
    static QString toDebugString(cv::Mat *mat);

private:

private:
    cv::Mat * mpCvMat=nullptr;
    QImage::Format mQFormat=QImage::Format_Invalid;
};

