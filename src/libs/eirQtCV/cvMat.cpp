#include "cvMat.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/types.hpp>

#include <eirXfr/Debug.h>

#include "cvBGRA.h"
#include "cvString.h"

cvMat::cvMat() {;}

cvMat::cvMat(const int rows, const int cols, const int type)
{
    TRACEQFI << rows << cols << type;
    mpCvMat = new cv::Mat(rows, cols, type);
    EXPECT(isValid());
    TRACE << dumpString();
}

cvMat::cvMat(const cv::Mat &otherMat)
{
    set(otherMat);
}

cvMat::~cvMat()
{
    clear();
}

bool cvMat::imread(const QString &fileName, const int imreadFlags)
{
    set(cv::imread(cvString(fileName), imreadFlags));
    return isValid();
}

int cvMat::cols() const
{
    return mat().cols;
}

int cvMat::rows() const
{
    return mat().rows;
}

int cvMat::type() const
{
    return mat().type();
}

bool cvMat::isNull() const
{
    return mat().rows <= 0 || mat().cols || nullptr == data();
}

bool cvMat::isValid() const
{
    if (isNull()) return false;
    // TODO more
    return true;
}

bool cvMat::isGreyType() const
{
    // note: really is single plane of unsigned char
    return 0 == type();
}

bool cvMat::isGreyData() const
{
    if (isGreyType()) return true;
    for (int r = 0; r < rows(); ++r)
    {
        quint32 *p = (quint32 *)(mat().ptr(r));
        for (int c = 0; c < cols(); ++c)
            if ( ! cvBGRA(*p++).isGrey()) return false;
    }
    return true;
}

bool cvMat::isGreyishData(signed epsilon) const
{
    if (isGreyType()) return true;
    for (int r = 0; r < rows(); ++r)
    {
        quint32 *p = (quint32 *)(mat().ptr(r));
        for (int c = 0; c < cols(); ++c)
            if ( ! cvBGRA(*p++).isGreyish(epsilon)) return false;
    }
    return true;
}

void cvMat::set(const cv::Mat other)
{
    mpCvMat = new cv::Mat(other);
}

void cvMat::set(const QSize sz)
{
    mpCvMat = new cv::Mat();
    mpCvMat->cols = sz.width(),
            mpCvMat->rows = sz.height();
}

void cvMat::set(const QImage &qimage)
{
    TRACEQFI << qimage;
    clear();
    QSize sz = qimage.size();
    DUMPVAL(sz);
    TRACE << "new cv::Mat()" << sz.height() << sz.width()
          << ((QImage::Format_Grayscale8
             == qimage.format()) ? CV_8U : CV_8UC4);
    mpCvMat = new cv::Mat(sz.height() , sz.width(),
                    QImage::Format_Grayscale8
                        == qimage.format() ? CV_8UC1 : CV_8UC4);
    TRACE << Qt::hex << mpCvMat->data << qimage.bits() << Qt::dec
            << QString("memcpy(0x%1, 0x%2, %3*%4=%5")
             .arg("uchar*")
             .arg("uchar*")
             .arg(mpCvMat->elemSize1()).arg(mpCvMat->total())
             .arg(mpCvMat->elemSize1() * mpCvMat->total())
             ;
    std::memcpy(mpCvMat->data, qimage.bits(),
                mpCvMat->elemSize1() * mpCvMat->total());
    TRACERTV();
}

QSize cvMat::toSize() const
{
    return QSize(cols(), rows());
}

QImage cvMat::toImage() const
{
    TRACEQFI << dumpString();
    QImage::Format f = (CV_8UC1 == mat().type())
                            ? QImage::Format_Grayscale8
                            : QImage::Format_RGB32;
    QImage image;
    if (mat().isContinuous())
    {
        image = QImage(mat().data, mat().cols, mat().rows, f);
    }
    else
    {
        image = QImage(cols(), rows(), f);
        for (int r = 0; r < rows(); ++r)
            std::memcpy(image.scanLine(r), mat().ptr(r), cols() * mat().elemSize());
    }
    TRACE << image;
    return image;
}

void cvMat::makeGrey(cvMat greyMat) const
{
    TRACEQFI << greyMat.dumpString() << dumpString();
    cv::cvtColor(mat(), greyMat.mat(), cv::COLOR_BGR2GRAY);
    TRACE << greyMat.dumpString();
}

cvMat cvMat::toGrey() const
{
    TRACEQFI << dumpString();
    cv::Mat gm;
    cv::cvtColor(mat(), gm, cv::COLOR_BGR2GRAY);
    TRACE << cvMat(gm).dumpString();
    return cvMat(gm);
}

void cvMat::clear()
{
    TRACEFN;
    if (mpCvMat)
    {
        TRACE << "release()" << Qt::hex << mpCvMat << Qt::dec;
        mpCvMat->release();
        TRACE << "delete" << Qt::hex << mpCvMat << Qt::dec;
        delete mpCvMat;
        TRACE << "nullptr" << Qt::hex << mpCvMat << Qt::dec;
        mpCvMat = nullptr;
    }
    TRACERTV();
}

cv::Mat cvMat::mat() const
{
    return  mpCvMat ? *mpCvMat : cv::Mat();
}

cv::Mat cvMat::mat()
{
    return  mpCvMat ? *mpCvMat : cv::Mat();
}

quint8 *cvMat::data() const
{
    return mat().data;
}

QString cvMat::dumpString() const
{
    return QString("cvMat size=%1x%2 type=%3 total=%4")
            .arg(mat().size().width).arg(mat().size().height)
            .arg(mat().type()).arg(mat().total());
}
