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
    cvMat(const cv::Mat &otherMat);
    ~cvMat();
    void clear();
    cv::Mat mat() const;
    cv::Mat mat();
    cv::Mat operator()() const;
    size_t totalPixels() const;
    size_t depthInBytes() const;
    size_t depth() const;
    size_t stride() const;
    bool isContinuous() const;
    qsizetype sizeInBytes() const;
    size_t bytesPerLine() const;
    void *data() const;
    const quint8 *cptr(const int row) const;
    quint8 *ptr(const int row) const;
    int cols() const;
    int rows() const;
    int type() const;
    bool isNull() const;
    bool isEmpty() const;
    QSize size() const;
    void set(const cv::Mat other);
    void setGrey(const QQImage &image);
    QQImage toGreyImage() const;
    QImage::Format qformat() const;
    QString dumpString() const;

private:
    cv::Mat * mpCvMat=nullptr;
    QImage::Format mQFormat=QImage::Format_Invalid;
};

