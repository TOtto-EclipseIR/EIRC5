//! @file {EIRC2 repo}/src/libs/eirQtCV/cvCascade-Parameters.cpp

#include "cvCascade.h"

#include <APP>
#include <eirType/Real.h>
#include <eirXfr/Debug.h>

cvCascade::Parameters::Parameters() { TRACEFN; }

double cvCascade::Parameters::factor() const
{
    return mFactor;
}

int cvCascade::Parameters::neighbors() const
{
    return mNeighbors;
}

int cvCascade::Parameters::flags() const
{
    return mFlags;
}

cvSize cvCascade::Parameters::minSize() const
{
    return mMinSize.isValid() ? mMinSize : QQSize::null;
}

cvSize cvCascade::Parameters::maxSize() const
{
    return mMaxSize.isValid() ? mMaxSize : QQSize::null;
}

void cvCascade::Parameters::setFactor(const qreal &factor)
{
    mFactor = factor;
}

void cvCascade::Parameters::setNeighbors(const unsigned &neighbors)
{
    mNeighbors = neighbors;
}

void cvCascade::Parameters::setMinSize(const cvSize &minSize)
{
    mMinSize = minSize;
}

void cvCascade::Parameters::setMaxSize(const cvSize &maxSize)
{
    mMaxSize = maxSize;
}

QString cvCascade::Parameters::methodString(const QQFileInfo &cascadeXmlInfo) const
{
    return QString("Factor=%1,Neighbors=%2,MinSize=%3x%4,MaxSize=%5x%6,%7")
                    .arg(factor(),5,'f',3).arg(neighbors())
                    .arg(minSize().width).arg(minSize().height)
                    .arg(maxSize().width).arg(maxSize().height)
                    .arg(cascadeXmlInfo.completeBaseName());
}

QVariant cvCascade::Parameters::toVariant() const
{
    return QVariant::fromValue(*this);
}

qreal cvCascade::Parameters::typeFactor(const cvCascade::Type type)
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

signed cvCascade::Parameters::neighborsForMinQuality(const unsigned minQual)
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


QStringList cvCascade::Parameters::toDebugStringList() const
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

