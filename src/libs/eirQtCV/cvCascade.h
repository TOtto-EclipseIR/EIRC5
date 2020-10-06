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
#ifdef QTCV_SETTINGS_HACK
        void calculate(const unsigned scaleFactor, const signed neigh, const unsigned minQual);
#else
        void calculate(const Type type,
                       const QQSize imageSize,
                       const QQSize coreSize);
        void calculate(const QSettings::SettingsMap &map,
                       const Type type,
                       const QQSize imageSize,
                       const QQSize coreSize);
#endif
        double factor() const;
        int neighbors() const;
        int flags() const;
        cvSize minSize() const;
        cvSize maxSize() const;
        QString methodString(const QQFileInfo &cascadeXmlInfo) const;
        QVariant toVariant() const;
        static qreal typeFactor(const cvCascade::Type type);
        QStringList dumpList() const;

    private:
        double parseFactor();

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
#ifdef QTCV_SETTINGS_HACK
    int detectRectangles(const QSettings::SettingsMap rectSettings,
                         const unsigned scaleFactor,
                         const signed neighbors,
                         const unsigned minQuality,
                         const cvMat &greyInputMat,
                         const bool showDetect=false,
                         const QQRect &region=QQRect());
#else
    int detectRectangles(const Settings::Key &groupKey,
                         const QQImage &inputImage,
                         const bool showDetect=false,
                         const QQRect &region=QQRect());
#endif
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
