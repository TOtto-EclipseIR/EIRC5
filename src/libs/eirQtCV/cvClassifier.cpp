#include "cvClassifier.h"

#include <APP>
#include <eirType/Real.h>
#include <eirXfr/Debug.h>

#include "cvRectVector.h"
#include "cvString.h"

cvClassifier::cvClassifier(const cvClassifierType &type) : mType(type) {;}

bool cvClassifier::loadCascade(const QQFileInfo &xmlFileInfo)
{
    mCascadeXmlInfo = xmlFileInfo;
    return load(cvString(xmlFileInfo.filePath()));
}

QQRectList cvClassifier::detectRectangles(const cvMat greyMat, const Parameters &parms,
                                const bool showDetect, const QQRect &region)
{
    TRACEQFI << showDetect << region;
    if (greyMat.isNull() || notLoaded()) return QQRectList();           /* /========\ */

    if (showDetect)
    {
        cv::imshow("DetectMat", greyMat.mat());
        cv::waitKey(5000);
    }

    cvRectVector rectVec;
    detectMultiScale(greyMat.mat(),
                        rectVec,
                        parms.factor(),
                        parms.neighbors(),
                        parms.flags(),
                        parms.minSize(),
                        parms.maxSize());

    return rectVec.toRectList();
}


// static
BasicName cvClassifier::typeName(cvClassifier::Type type)
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

/* ----------------------- Parameters ------------------------ */

cvClassifier::Parameters::Parameters() { TRACEFN; }

double cvClassifier::Parameters::factor() const
{
    return mFactor;
}

int cvClassifier::Parameters::neighbors() const
{
    return mNeighbors;
}

int cvClassifier::Parameters::flags() const
{
    return mFlags;
}

cvSize cvClassifier::Parameters::minSize() const
{
    return mMinSize.isValid() ? mMinSize : QQSize::null;
}

cvSize cvClassifier::Parameters::maxSize() const
{
    return mMaxSize.isValid() ? mMaxSize : QQSize::null;
}

void cvClassifier::Parameters::setFactor(const qreal &factor)
{
    mFactor = factor;
}

void cvClassifier::Parameters::setNeighbors(const unsigned &neighbors)
{
    mNeighbors = neighbors;
}

void cvClassifier::Parameters::setMinSize(const cvSize &minSize)
{
    mMinSize = minSize;
}

void cvClassifier::Parameters::setMaxSize(const cvSize &maxSize)
{
    mMaxSize = maxSize;
}

QString cvClassifier::Parameters::methodString(const QQFileInfo &cascadeXmlInfo) const
{
    return QString("Factor=%1,Neighbors=%2,MinSize=%3x%4,MaxSize=%5x%6,%7")
                    .arg(factor(),5,'f',3).arg(neighbors())
                    .arg(minSize().width).arg(minSize().height)
                    .arg(maxSize().width).arg(maxSize().height)
                    .arg(cascadeXmlInfo.completeBaseName());
}

QVariant cvClassifier::Parameters::toVariant() const
{
    return QVariant::fromValue(*this);
}

qreal cvClassifier::Parameters::typeFactor(const cvClassifier::Type type)
{
    qreal resultFactor = qQNaN();
    switch (type)
    {
    case PreScan:
    case PreScanAll:
    case Face:          resultFactor = 1.0 / 3.0;       break;
    default:            MUSTDO(others);                 break;
    }
    BEXPECTNOT(qIsNaN(resultFactor));
    return resultFactor;
}

signed cvClassifier::Parameters::neighborsForMinQuality(const unsigned minQual)
{
    if (false)                      ;
    else if (minQual > 975)     return 96;
    else if (minQual > 950)     return 64;
    else if (minQual > 900)     return 40;
    else if (minQual > 850)     return 32;
    else if (minQual > 800)     return 24;
    else if (minQual > 750)     return 16;
    else if (minQual > 700)     return 12;
    else if (minQual > 650)     return 8;
    else if (minQual > 600)     return 6;
    else if (minQual > 500)     return 4;
    else if (minQual > 400)     return 3;
    else if (minQual > 200)     return 2;
    else                        return 1;
}


QStringList cvClassifier::Parameters::toDebugStringList() const
{
    QStringList qsl;
    qsl << QString("%1 = %2").arg("factor").arg(factor());
    qsl << QString("%1 = %2").arg("neighbors").arg(neighbors());
    qsl << QString("%1 = %2").arg("flags").arg(flags());
    qsl << QString("%1 = %2x%3").arg("minSize").arg(minSize().width)
                                               .arg(minSize().height);
    qsl << QString("%1 = %2x%3").arg("maxSize").arg(maxSize().width)
                                               .arg(maxSize().height);
    return qsl;
}
