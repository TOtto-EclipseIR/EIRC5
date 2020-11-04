#pragma once
#include "eirObjDet.h"

#include <QObject>

#include <eirExe/Settings.h>
#include <eirQtCV/cvClassifier.h>
#include <eirQtCV/cvMat.h>
#include <eirType/QQImage.h>
#include <eirType/QQRectList.h>

#include "ObjDetResultList.h"
#include "RectangleFinder.h"
#include "RectangleGrouper.h"

class EIROBJDET_EXPORT ObjDetProcessor : public QObject
{
    Q_OBJECT
public:
    ObjDetProcessor(const cvClassifier::Type cascadeType,
                    const Settings::Key objDetKey,
                    QObject * parent=nullptr);
    cvClassifier::Type type() const         { return cmType; }
    RectangleFinder *finder()               { return mpRectFinder; }
    RectangleGrouper *grouper()             { return mpRectGrouper; }
    QQDir detectorBaseDir()                 { return finder()->baseDir(); }
    QQRectList rectangleList() const        { return mRectList; }

public slots:
    void initialize();
    void reset();

signals:
    void setupFinished();
    void resetd();

public:
    void setImage(const QQImage &inputImage);
    XerReturn<QQRectList> findRects(const bool showMat=false, const QQRect &region=QQRect());
    int groupRects();

    QImage inputImage() const               { return mInputImage; }
    QImage detectImage() const              { return mGreyInputMat.toGreyImage(); }
    QQString methodString() const           { return mMethodString; }
    QQRectList rectList() const             { return mRectList; }
    ObjDetResultList resultList() const     { return mResultList; }
    bool isError() const                    { return mError.isError(); }
    XerEntry error() const                  { return mError; }

private:
    const cvClassifier::Type cmType=cvClassifier::nullType;
    Settings::Key mResourceKey;
    Settings::Key mObjDetTypeKey;
    RectangleFinder * mpRectFinder=nullptr;
    RectangleGrouper * mpRectGrouper=nullptr;
    XerEntry mError;
    QQImage mInputImage;
    cvMat mGreyInputMat;
    QQString mMethodString;
    QQRectList mRectList;
    ObjDetResultList mResultList;
};

