#pragma once
#include "eirQtCV.h"

#include <QFileInfo>
#include <QImage>
#include <QList>
#include <QPair>
#include <QSize>
#include <QString>
#include <QStringList>

#include <eirType/BasicName.h>
#include <eirType/QQFileInfo.h>
#include <eirExe/Configuration.h>
#include <eirCascade/CascadeParameters.h>
#include <eirCascade/CascadeType.h>

#include "cvMat.h"

#include <eirCascade/CascadeParameters.h>

namespace cv { class CascadeClassifier; }

class EIRQTCV_EXPORT cvCascade
{
public:
    typedef QList<QRect> RectList;

public:
    cvCascade(const CascadeType &cascadeType=CascadeType::nullCascadeType);
    void configure(const Configuration &config);
    CascadeType cascadeType() const;
    bool loadCascade(const QFileInfo &cascadeXmlInfo);
    bool notLoaded() const;
    bool isLoaded() const;
    void unload();
    QSize coreSize() const;
    QFileInfo cascadeFileInfo() const;
    cv::CascadeClassifier *cascade();
    bool imreadInputMat(const QQFileInfo &inputFileInfo);
    RectList detect();
    QString methodString() const;
    QString imwriteMarkedImage(QQFileInfo markFileInfo);

private:
    bool getCoreSize(const QFileInfo &cascadeXmlInfo);
    void makeMethodString(const CascadeParameters &parms);

private:
    const CascadeType cmCascadeType;
    Configuration mCascadeConfig;
//    CascadeParameters mParameters;
    QFileInfo mCascadeXmlInfo;
    cv::CascadeClassifier *mpCascade=nullptr;
    QSize mCoreSize;
    cvMat mInputMat;
    cvMat mDetectMat;
    QString mMethodString;
    RectList mRectList;
    QImage mMarkedImage;
};

