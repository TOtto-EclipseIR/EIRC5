#pragma once
#include "eirQtCV.h"

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/core/types.hpp>

#include <eirExe/Settings.h>
#include <eirType/QQRect.h>
#include <eirType/QQRectList.h>
#include <eirXfr/XerReturn.h>

#include "cvMat.h"
#include "cvSize.h"

template class EIRQTCV_EXPORT XerReturn<QQRectList>;

class EIRQTCV_EXPORT cvClassifier : public cv::CascadeClassifier
{
public:
    enum Type
    {
        nullType = 0,
        PreScan, PreScanAll, Face, LeftEye, RighttEye,
        BothEyes, Nose, Mouth, LeftProfile, RightProfile,
        sizeType
    };
    typedef cvClassifier::Type cvClassifierType;

    class EIRQTCV_EXPORT Parameters
    {
    public:
        Parameters();
        double factor() const                           { return mFactor; }
        int neighbors() const                           { return mNeighbors; }
        int flags() const                               { return mFlags; }
        cvSize minSize() const                          { return mMinSize; }
        cvSize maxSize() const                          { return mMaxSize; }
        bool preScanMerge() const                       { return mPreScanMerge; }
        void setFactor(const qreal &factor)             { mFactor = factor; }
        void setNeighbors(const unsigned &neighbors)    { mNeighbors = neighbors; }
        void setMinSize(const cvSize &minSize)          { mMinSize = minSize; }
        void setMaxSize(const cvSize &maxSize)          { mMaxSize = maxSize; }
        void setPreScanMerge(const bool merge)          { mPreScanMerge = merge; }

        QString methodString(const QQFileInfo &cascadeXmlInfo) const;
        QVariant toVariant() const;
        static qreal typeFactor(const cvClassifierType type);
        QStringList toDebugStringList() const;

    public: // static
        static signed neighborsForPreScanQuality(const unsigned minQual);

    private:
        Settings::Key mGroupKey;
        qreal mFactor=Q_QNAN;
        unsigned mNeighbors=0;
        int mFlags=0;
        cvSize mMinSize;
        cvSize mMaxSize;
        bool mPreScanMerge=true;
    };

public:
    cvClassifier(const cvClassifierType  &type=nullType);
    Type type() const                   { return mType; }
    BasicName typeName() const          { return typeName(mType); }

    void initialize();
    bool loadCascade(const QQFileInfo &xmlFileInfo);
    bool isLoaded() const               { return ! notLoaded(); }
    bool notLoaded() const              { return empty(); }
    QQSize coreSize() const             { return cvSize(getOriginalWindowSize()).toSize(); }
    QQFileInfo cascadeFileInfo() const  { return mCascadeXmlInfo; }
    XerReturn<QQRectList> detectRectangles(const cvMat greyMat,  const Parameters &parms,
                                           const bool showDetect=false,  const QQRect &region=QQRect());
public: // static
    static BasicName typeName(Type type);

private:
    cvClassifierType mType;
    QQFileInfo mCascadeXmlInfo;
};
Q_DECLARE_METATYPE(cvClassifier::Parameters);

