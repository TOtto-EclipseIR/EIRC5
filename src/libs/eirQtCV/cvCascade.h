#pragma once
#include "eirQtCV.h"

#include <QFileInfo>
#include <QImage>
#include <QList>
#include <QPair>
#include <QSize>
#include <QString>
#include <QStringList>

#include <eirBase/Typedefs.h>
#include <eirBase/Uuid.h>
#include <eirType/BasicName.h>
#include <eirType/Boolean.h>
#include <eirType/QQFileInfo.h>
#include <eirType/QQImage.h>
#include <eirType/QQRect.h>
#include <eirType/QQRectList.h>
#include <eirType/QQSize.h>
#include <eirExe/Configuration.h>

#include "cvMat.h"


namespace cv { class CascadeClassifier; }

class EIRQTCV_EXPORT cvCascade
{
public:
    enum Type
    {
        nullType = 0,
        PreScan, PreScanAll, Face, LeftEye, RighttEye,
        BothEyes, Nose, Mouth, LeftProfile, RightProfile,
        sizeType
    };
    class EIRQTCV_EXPORT Parameters
    {
    public:
        Parameters();
        Parameters(const QVariant &variant);
        Parameters(const Configuration &cascadeConfig);
        Configuration &cascadeConfig();
        void set(const Configuration &cascadeConfig);
        void calculate(const Type type,
                       const QQSize imageSize,
                       const QQSize coreSize);
        double factor() const;
        int neighbors() const;
        int flags() const;
        QQSize minSize() const;
        QQSize maxSize() const;
        QString methodString(const QFileInfo &cascadeXmlInfo) const;
        QVariant toVariant() const;
        QStringList dumpList() const;

    private:
        double parseFactor();

    private:
        Configuration mConfig;
        double mFactor=Q_QNAN;
        int mNeighbors=0;
        int mFlags=0;
        QQSize mMinSize;
        QQSize mMaxSize;
    };


public:
    cvCascade(const Type &type=Type::nullType);
    Type type() const;
    BasicName typeName() const;
    bool isNull() const;
    bool loadCascade(const QFileInfo &cascadeXmlInfo);
    bool loadCoreSize(const QFileInfo &cascadeXmlInfo,
                      int cascadeVersion=0);
    bool notLoaded() const;
    bool isLoaded() const;
    void unload();
    QSize coreSize() const;
    QQFileInfo cascadeFileInfo() const;
    cv::CascadeClassifier *classifier();

    int detectRectangles(const Configuration &rectFinderConfig,
                         const QQImage &inputImage,
                         const bool showDetect=false,
                         const QQRect &region=QQRect());
    cvMat detectMat() const;
    QQImage detectImage() const;
    QQRectList rectList() const;
    QString methodString() const;
    Parameters parameters() const;

public: // static
    static BasicName typeName(Type type);

private:
    Type cmType=nullType;
    QQFileInfo mCascadeXmlInfo;
    cv::CascadeClassifier *mpClassifier=nullptr;
    QSize mCoreSize;
    // side-effects of detectRectangles()
    cvMat mDetectMat;
    QQRectList mRectList;
    QString mMethodString;
    Parameters mParameters;
};
Q_DECLARE_METATYPE(cvCascade::Parameters);
typedef cvCascade::Type cvCascadeType;
