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
#include "cvString.h"

cvMat::cvMat() {;}

cvMat::cvMat(const int rows, const int cols, const int type)
{
    TRACEQFI << rows << cols << type;
    mpCvMat = new cv::Mat(rows, cols, type);
    //EXPECT(isValid());
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

size_t cvMat::depth() const
{
    return depthInBytes() * 8;
}

size_t cvMat::stride() const
{
    return mat().step;
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

quint8 *cvMat::ptr(const int row) const
{
    return mat().ptr(row);
}

const quint8 *cvMat::cptr(const int row) const
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

void cvMat::set(const cv::Mat other)
{
    mpCvMat = new cv::Mat(other);
}

void cvMat::setGrey(const QQImage &image)
{
    TRACEQFI << image;
    EXPECTNOT(image.isNull());
    clear();
    if (image.isNull()) return;                             /* /=========\ */
    QQImage greyImage = image.convertToFormat(QImage::Format_Grayscale8);
    EXPECTEQ(8, greyImage.depth());
    mpCvMat = new cv::Mat(image.height(), image.width(), CV_8UC1);
    TSTALLOC(mpCvMat->ptr());
    EXPECTEQ(greyImage.depth(), int(depth()));
    if (greyImage.depth() != int(depth()))
        return;                                             /* /=========\ */
    if (isContinuous() && greyImage.stride() == int(stride()))
    {
        EXPECTEQ(greyImage.sizeInBytes(), int(sizeInBytes()));
        if (greyImage.sizeInBytes() != int(sizeInBytes()))
            return;                                             /* /=========\ */
        std::memcpy(mpCvMat->ptr(), greyImage.bits(), sizeInBytes());
    }
    else
    {
        BEXPECTEQ(greyImage.rows(), rows());
        for (int r = 0; r < rows(); ++r)
        {
            const quint8 *pImage = greyImage.scanLine(r);
            quint8 *pMat = ptr(r);
            std::memcpy(pMat, pImage, bytesPerLine());
        }
    }
    mQFormat = QImage::Format_Grayscale8;
    TRACERTV();
}

QQImage cvMat::toGreyImage() const
{
    TRACEQFI << dumpString();
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
            const quint8 *pMat = cptr(r);
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

QString cvMat::dumpString() const
{
    return QString("cvMat size=%1x%2 type=%3 total=%4 data=%5")
            .arg(mat().size().width).arg(mat().size().height)
            .arg(mat().type()).arg(sizeInBytes())
            .arg(PTRSTRING(data()));
}
