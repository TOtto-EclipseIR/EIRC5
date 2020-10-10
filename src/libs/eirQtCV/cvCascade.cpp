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
#include "cvRectVector.h"
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

cv::CascadeClassifier *cvCascade::classifier() const
{
    return mpClassifier;
}

QQRectList cvCascade::detectRectangles(const cvMat greyMat, const Parameters &parms,
                                const bool showDetect, const QQRect &region) const
{
    TRACEQFI << showDetect << region;
    TSTALLOC(mpClassifier);
    if (greyMat.isNull() || notLoaded()) return QQRectList();           /* /========\ */

    if (showDetect)
    {
        cv::imshow("DetectMat", greyMat.mat());
        cv::waitKey(5000);
    }

    cvRectVector rectVec;
    classifier()->detectMultiScale(greyMat.mat(),
                        rectVec,
                        parms.factor(),
                        parms.neighbors(),
                        parms.flags(),
                        parms.minSize(),
                        parms.maxSize());

    return rectVec.toRectList();
}

// static
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
