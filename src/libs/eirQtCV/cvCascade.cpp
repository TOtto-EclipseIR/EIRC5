#include "cvCascade.h"

#include <QDomElement>
#include <QColor>
#include <QTextStream>
#include <QDomElement>
#include <QPainter>
#include <QPixmap>

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/core/types.hpp>

#include <eirExe/XmlFile.h>
#include <eirXfr/Debug.h>

#include "cvRect.h"
#include "cvString.h"

cvCascade::cvCascade(const cvCascade::Type &type)
    : cmType(type)
    , mpClassifier(new cv::CascadeClassifier())
{
    TRACEQFI << type;
    TSTALLOC(mpClassifier);
    TODO(cv::redirectError);
}

cvCascade::Type cvCascade::type() const
{
    return cmType;
}

BasicName cvCascade::typeName() const
{
    return typeName(cmType);
}

bool cvCascade::loadCascade(const QQFileInfo &cascadeXmlInfo)
{
    TRACEQFI << typeName()() << cascadeXmlInfo.absoluteFilePath();
    EXPECT(mpClassifier->load(cvString(cascadeXmlInfo.absoluteFilePath())));
    mCascadeXmlInfo = cascadeXmlInfo;
    return isLoaded();
}

bool cvCascade::isLoaded() const
{
    return ! notLoaded();
}

bool cvCascade::notLoaded() const
{
    return mpClassifier->empty();
}

QSize cvCascade::coreSize() const
{
    TSTALLOC(mpClassifier);
    cv::Size cvsz = mpClassifier->getOriginalWindowSize();
    QSize qsz(cvsz.width, cvsz.height);
    TRACEQFI << qsz;
    return qsz;
}

QQFileInfo cvCascade::cascadeFileInfo() const
{
    return mCascadeXmlInfo;
}

cv::CascadeClassifier *cvCascade::classifier()
{
    return mpClassifier;
}

int cvCascade::detectRectangles(const cvMat greyMat,
                                const Settings::Key groupKey,
                                const bool showDetect,
                                const QQRect &region)
{
    TRACEQFI << showDetect << region;
    TSTALLOC(mpClassifier);

    mDetectMat = greyMat;
    DUMP << mDetectMat.toDebugString();
    if (mDetectMat.isNull()) return -2; // null cvMat       /* /========\ */
    if (showDetect)
    {
        cv::imshow("DetectMat", mDetectMat.mat());
        cv::waitKey(5000);
    }

    if (notLoaded()) return -3;         // empty cascade    /* /========\ */
    //mParameters.set(groupKey);
    MUSTDO(mParameters.calculate(cmType, mDetectMat.size(), coreSize()))
    mMethodString = mParameters.methodString(mCascadeXmlInfo);
    DUMPVAL(mMethodString);

    std::vector<cv::Rect> cvRectVector;

    classifier()->detectMultiScale(mDetectMat.mat(),
                        cvRectVector,
                        mParameters.factor(),
                        mParameters.neighbors(),
                        mParameters.flags(),
                        mParameters.minSize(),
                        mParameters.maxSize());

    foreach (cvRect cvrc, cvRectVector) mRectList << cvrc.toRect();
    return mRectList.size();
}

cvMat cvCascade::detectMat() const
{
    return mDetectMat;
}

QQImage cvCascade::detectImage() const
{
    return mDetectMat.toGreyImage();
}

QQRectList cvCascade::rectList() const
{
    return mRectList;
}

QString cvCascade::methodString() const
{
    return mMethodString;
}

cvCascade::Parameters cvCascade::parameters() const
{
    return mParameters;
}

BasicName cvCascade::typeName(cvCascade::Type type)
{
    switch (type)
    {
        case nullType:      return "{null}";
        case PreScan:       return "PreScan";
        default:
            MUSTDO(type);
            break;
    }
    return "{unknown}";
}
