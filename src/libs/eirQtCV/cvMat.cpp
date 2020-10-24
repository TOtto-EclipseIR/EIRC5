#include "cvMat.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/types.hpp>

#include <eirBase/eirBase.h>
#include <eirType/QQRect.h>
#include <eirType/QQSize.h>
#include <eirXfr/Debug.h>

#include "cvBGRA.h"
#include "cvSize.h"
#include "cvString.h"

cvMat::cvMat() {;}

cvMat::cvMat(const int rows, const int cols, const int type)
{
    TRACEQFI << rows << cols << type;
    mpCvMat = new cv::Mat(rows, cols, type);
    //EXPECT(isValid());
    TRACE << toDebugString();
}

cvMat::cvMat(cv::Mat &otherMat)
{
    set(&otherMat);
}

cvMat::~cvMat() { NEEDDO(clear()); }

void cvMat::clear()
{
    TRACEFN;
    if (mpCvMat)
    {
        TRACE << "release()" << PTRSTRING(mpCvMat);
        mpCvMat->release();
        TRACE << "delete" << PTRSTRING(mpCvMat);
        delete mpCvMat;
        TRACE << "nullptr" << PTRSTRING(mpCvMat);
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

cv::Mat cvMat::operator()() const
{
    return mat();
}

size_t cvMat::totalPixels() const
{
    return mat().total();
}

size_t cvMat::depthInBytes() const
{
    return mat().elemSize();
}

int cvMat::depth() const
{
    return int(depthInBytes() * 8);
}

int cvMat::stride() const
{
    return int(mat().step);
}

bool cvMat::isContinuous() const
{
    return mat().isContinuous();
}

qsizetype cvMat::sizeInBytes() const
{
    return rows() * bytesPerLine();
}

size_t cvMat::bytesPerLine() const
{
    return cols() * depthInBytes();
}

void *cvMat::data() const
{
    return mat().data;
}

quint8 *cvMat::ptr(const int row)
{
    return mat().ptr(row);
}

const quint8 *cvMat::ptr(const int row) const
{
    return mat().ptr(row);
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
    return mat().rows <= 0 || mat().cols <= 0 || nullptr == data();
}

bool cvMat::isEmpty() const
{
    return mat().empty();
}

QSize cvMat::size() const
{
    return QSize(cols(), rows());
}

void cvMat::set(cv::Mat *other)
{
    mpCvMat = other;
}


QQImage cvMat::toGreyImage() const
{
    TRACEQFI << toDebugString();
    EXPECTEQ(CV_8UC1, type());
    if (CV_8UC1 != type()) return QQImage();
#if 1
    QQImage greyImage(cols(), rows(), QImage::Format_Grayscale8);
    EXPECTEQ(1, greyImage.depth());
    EXPECTEQ(greyImage.size().area(), greyImage.sizeInBytes());
    EXPECTEQ(size_t(greyImage.depth()), depth());
    EXPECTEQ(size_t(greyImage.stride()), stride());
    EXPECTEQ(qsizetype(greyImage.sizeInBytes()), sizeInBytes());
    TODO(WhyDifferentSizeTypes);
    BEXPECTNE(nullptr, greyImage.bits());
    BEXPECTNE(nullptr, mpCvMat->ptr());
    if (isContinuous() && greyImage.stride() == int((stride())))
    {
        TRACE << PTRSTRING(greyImage.bits()) << PTRSTRING(data())
              << greyImage.sizeInBytes() << sizeInBytes();
        if (greyImage.sizeInBytes() != sizeInBytes())
            return QQImage();
        std::memcpy(greyImage.bits(), data(), sizeInBytes());
    }
    else
    {
        BEXPECTEQ(greyImage.rows(), rows());
        for (int r = 0; r < rows(); ++r)
        {
            quint8 *pImage = greyImage.scanLine(r);
            const quint8 *pMat = ptr(r);
            std::memcpy(pImage, pMat, greyImage.bytesPerLine());
        }
    }
#else
    QQImage greyImage(data(), cols(), rows(), QImage::Format_Grayscale8);
#endif
    EXPECTNOT(greyImage.isNull())
    return greyImage;
}

QImage::Format cvMat::qformat() const
{
    return mQFormat;
}

QString cvMat::toDebugString() const
{
    return toDebugString(mpCvMat);
}

// static
cvMat cvMat::greyFromImage(const QQImage &image)
{
    TRACEQFI << image;
    cvMat newMat(image.height(), image.width(), CV_8UC1);
    TRACE << toDebugString(newMat.mpCvMat);
    TSTALLOC(newMat.mat().data);
    QQImage greyImage = image.convertToFormat(QImage::Format_Grayscale8);
    EXPECTEQ(8, greyImage.depth());
    EXPECTEQ(greyImage.size(), newMat.size());
    EXPECTEQ(8, newMat.depth());
    BEXPECTEQ(greyImage.depth(), newMat.depth());
    if (greyImage.size() != newMat.size() || greyImage.depth() != newMat.depth())
        return cvMat();                                             /* /=========\ */

    if (newMat.isContinuous())
    {
        EXPECTEQ(greyImage.stride(), newMat.stride());
        EXPECTEQ(greyImage.sizeInBytes(), newMat.sizeInBytes());
    }
    if (newMat.isContinuous()
            && greyImage.stride() == newMat.stride()
            && greyImage.sizeInBytes() == newMat.sizeInBytes())
    {
            std::memcpy(newMat.ptr(0), greyImage.bits(), newMat.sizeInBytes());
    }
    else
    {
        for (int r = 0; r < newMat.rows(); ++r)
        {
            const quint8 *pImage = greyImage.scanLine(r);
            quint8 *pMat = newMat.ptr(r);
            std::memcpy(pMat, pImage, newMat.bytesPerLine());
        }
    }
    newMat.mQFormat = QImage::Format_Grayscale8;
    return newMat;
}

// static
QString cvMat::toDebugString(cv::Mat *mat)
{
    return (nullptr == mat)
            ? "Null cv::Mat"
            : QString("cvMat size=%1x%2 type=%3 depth=%4 total=%5 data=%6")
                    .arg(mat->size().width).arg(mat->size().height)
                    .arg(mat->type()).arg(mat->elemSize())
                    .arg(mat->elemSize() * mat->total())
                    .arg(PTRSTRING(mat->data));
}

