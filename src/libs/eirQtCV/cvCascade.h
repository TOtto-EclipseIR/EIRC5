#pragma once
#include "eirQtCV.h"

#include <QImage>
#include <QList>
#include <QPair>
#include <QSize>
#include <QString>
#include <QStringList>

#include <eirBase/Typedefs.h>
#include <eirBase/Uuid.h>
#include <eirExe/Settings.h>
#include <eirType/BasicName.h>
#include <eirType/Boolean.h>
#include <eirType/QQFileInfo.h>
#include <eirType/QQImage.h>
#include <eirType/QQRect.h>
#include <eirType/QQRectList.h>
#include <eirType/QQSize.h>

#include "cvMat.h"
#include "cvSize.h"

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
        void set(const Settings::Key &groupKey);
        //void calculate(const Type type, const QQSize imageSize, const QQSize coreSize);
        double factor() const;
        int neighbors() const;
        int flags() const;
        cvSize minSize() const;
        cvSize maxSize() const;

        void setFactor(const qreal &factor);
        void setNeighbors(const unsigned &neighbors);
        void setMinSize(const cvSize &minSize);
        void setMaxSize(const cvSize &maxSize);

        QString methodString(const QQFileInfo &cascadeXmlInfo) const;
        QVariant toVariant() const;
        static qreal typeFactor(const cvCascade::Type type);
        QStringList dumpList() const;



    private: // static
        static signed neighborsForMinQuality(const unsigned minQual);

    private:
        Settings::Key mGroupKey;
        qreal mFactor=Q_QNAN;
        unsigned mNeighbors=0;
        int mFlags=0;
        cvSize mMinSize;
        cvSize mMaxSize;
    };


public:
    cvCascade(const Type &type);
    Type type() const;
    BasicName typeName() const;
    bool loadCascade(const QQFileInfo &cascadeXmlInfo);
    bool isLoaded() const;
    bool notLoaded() const;
    QSize coreSize() const;
    QQFileInfo cascadeFileInfo() const;
    cv::CascadeClassifier *classifier();
    int detectRectangles(const cvMat greyMat, const Settings::Key groupKey,
                         const bool showDetect=false, const QQRect &region=QQRect());
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
    // side-effects of detectRectangles()
    cvMat mDetectMat;
    QQRectList mRectList;
    QString mMethodString;
    Parameters mParameters;
};
Q_DECLARE_METATYPE(cvCascade::Parameters);
typedef cvCascade::Type cvCascadeType;
