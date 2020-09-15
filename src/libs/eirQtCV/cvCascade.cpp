#include "cvCascade.h"

#include <QColor>
#include <QPainter>
#include <QPixmap>

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>

#include <eirXfr/Debug.h>
#include <eirCascade/CascadeParameters.h>

#include "cvString.h"

cvCascade::cvCascade(const CascadeType &cascadeType)
    : cmCascadeType(cascadeType)
{
    TRACEQFI << cascadeType.name();
}

void cvCascade::configure(const Configuration &config)
{
    TRACEFN;
    config.dump();
    mCascadeConfig = config;
    //mParameters.configureCascade(config);
}

CascadeType cvCascade::cascadeType() const
{
    return cmCascadeType;
}

bool cvCascade::loadCascade(const QFileInfo &cascadeXmlInfo)
{
    TRACEQFI << cascadeType().name() << cascadeXmlInfo;
    unload();
    cv::CascadeClassifier * pcvcc = new cv::CascadeClassifier;
    if (pcvcc->load(cvString(cascadeXmlInfo.absoluteFilePath())))
    {
        mpCascade = pcvcc;
        mCascadeXmlInfo = cascadeXmlInfo;
    }
    EXPECTNOT(mpCascade->empty());
    return nullptr != mpCascade;
}

bool cvCascade::notLoaded() const
{
    return mpCascade ? mpCascade->empty() : true;
}

bool cvCascade::isLoaded() const
{
    return mpCascade ? (! mpCascade->empty()) : false;
}

void cvCascade::unload()
{
    if (mpCascade)
    {
        delete mpCascade;
        mpCascade = nullptr;
    }
    mCascadeXmlInfo = QFileInfo();
    mCoreSize = QSize();
}

QSize cvCascade::coreSize() const
{
    return mCoreSize;
}

QFileInfo cvCascade::cascadeFileInfo() const
{
    return mCascadeXmlInfo;
}

cv::CascadeClassifier *cvCascade::cascade()
{
    return mpCascade;
}

bool cvCascade::imreadInputMat(const QQFileInfo &inputFileInfo)
{
    TRACEQFI << inputFileInfo;
    mInputMat.imread(inputFileInfo.absoluteFilePath(), cv::IMREAD_COLOR);
    TRACE << mInputMat.dumpString();
    EXPECT(mInputMat.isValid());
    return mInputMat.isValid();
}

cvCascade::RectList cvCascade::detect()
{
    TRACEQFI << mInputMat.dumpString();
    TODO(inputSize&coreSize);
    CascadeParameters parms(mCascadeConfig);
    parms.calculate(mInputMat.toSize(), QSize(32,32));
    QSize minSize = parms.minSize();
    QSize maxSize = parms.maxSize();
    cvMat detectMat(mInputMat.rows(), mInputMat.cols(), CV_8UC1);
    mInputMat.makeGrey(detectMat.mat());
    mDetectMat.set(detectMat.mat());
    std::vector<cv::Rect> cvRectVector;
    cvCascade::RectList results;
    makeMethodString(parms);
    TRACE << methodString();

    mpCascade->detectMultiScale(detectMat.mat(),
                        cvRectVector,
                        parms.factor(),
                        parms.neighbors(),
                        parms.flags(),
                        cv::Size(minSize.width(), minSize.height()),
                        cv::Size(maxSize.width(), maxSize.height()));

    foreach (cv::Rect cvrc, cvRectVector)
    {
        QRect qrc(cvrc.x, cvrc.y, cvrc.width, cvrc.height);
        results << qrc;
    }

    TRACE << results.size() << "Rectangles";
    mRectList = results;
    return results;
}

QString cvCascade::methodString() const
{
    return mMethodString;
}

QString cvCascade::imwriteMarkedImage(QQFileInfo markFileInfo)
{
    TRACEQFI << markFileInfo;
    cv::Mat markMat;
    mInputMat.mat().copyTo(markMat);

#if 0
    foreach (QRect qrc, mRectList)
        cv::rectangle(markMat,
                      cv::Rect(qrc.left(), qrc.top(), qrc.width(), qrc.height()),
                      cv::Scalar(255, 255, 0),
                      3);
#else
    RMUSTDO(RemoveForFlight);
    foreach (QRect qrc, mRectList)
        cv::rectangle(markMat,
                      cv::Rect(qrc.left(), qrc.top(), qrc.width(), qrc.height()),
                      cv::Scalar(255, 0, 0),
                      1);

#endif

    markFileInfo.replace("%M", methodString());
    return  cv::imwrite(cvString(markFileInfo.absoluteFilePath()), markMat)
            ? markFileInfo.absoluteFilePath()
            : "Error writing MarkedRect file";
}

bool cvCascade::getCoreSize(const QFileInfo &cascadeXmlInfo)
{
    TRACEQFI << cascadeXmlInfo;
    mCoreSize = QSize(32, 32);
    NEEDDO(it);
    return false;
}

void cvCascade::makeMethodString(const CascadeParameters &parms)
{
    TRACEFN;
    parms.dumpList();
    mMethodString = QString("Factor=%1,Neighbors=%2"
                            ",MinSize=%3x%4,MaxSize=%5x%6,%7")
            .arg(parms.factor()).arg(parms.neighbors())
            .arg(parms.minSize().width()).arg(parms.minSize().height())
            .arg(parms.maxSize().width()).arg(parms.maxSize().height())
            .arg(mCascadeXmlInfo.completeBaseName());

}

