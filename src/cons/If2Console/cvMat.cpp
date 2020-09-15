//! \file cvMat.cpp
#include "cvMat.h"

#include <QTemporaryFile>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

#include "cvSize.h"

#include <eirXfr/Debug.h>

cvMat::cvMat() {;}

cv::Mat cvMat::mat() const
{
    return mCvMat;
}

cv::Mat cvMat::cvtColor(const int code) const
{
    cv::Mat outMat;
    cv::cvtColor(mCvMat, outMat, code);
    return outMat;
}

bool cvMat::isEmpty() const
{
    return mCvMat.empty();
}

cv::Mat cvMat::cvtGrey() const
{
    return cvtColor(cv::COLOR_BGR2GRAY);
}

bool cvMat::loaded() const
{
    return ! isEmpty();
}

bool cvMat::load(const QString &fileName)
{
    TRACEQFI << QFileInfo(fileName).absoluteFilePath();
    set(cv::imread(fileName.toStdString()));
    return loaded();
}

bool cvMat::save(const QString &fileName)
{
    TRACEQFI << fileName << mCvMat.size;
    return cv::imwrite(fileName.toStdString(),  mCvMat);
}

void cvMat::set(const QImage &qimage)
{
    WEXPECT(fromImage(qimage));
}

void cvMat::set(const cv::Mat &other)
{
    mCvMat = other;
}

QImage cvMat::toImage(const QImage::Format qformat, const QByteArray &mimeFormat)
{
    TRACEQFI << qformat << mimeFormat;
    QTemporaryFile imwriteFile("imwrite" + mimeFormat);
    EXPECT(imwriteFile.open());
    QString imwriteTempFilePath = imwriteFile.fileName();
    EXPECTNOT(imwriteTempFilePath.isEmpty());
    imwriteFile.close();
    EXPECT(cv::imwrite(imwriteTempFilePath.toStdString(), mat()));
    QImage imwriteImage(imwriteTempFilePath);
    QImage resultImage = imwriteImage.convertToFormat(qformat);
    WEXPECTNOT(resultImage.isNull());
    return resultImage;
}

bool cvMat::fromImage(const QImage &qimage)
{
    TRACEQFI << qimage.size() << qimage.format();
    if (qimage.isNull()) return false;
    mCvMat.create(cvSize(qimage.size()),
        qimage.format() == QImage::Format_Grayscale8
            ? CV_8U : CV_8UC3);
    memcpy(mCvMat.ptr(), qimage.bits(), qimage.sizeInBytes());
    return true;
}

int cvMat::cols() const
{
    return mCvMat.cols;
}

int cvMat::rows() const
{
    return mCvMat.rows;
}
