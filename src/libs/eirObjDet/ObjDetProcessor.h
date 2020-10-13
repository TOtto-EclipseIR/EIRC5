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
#include "RectFinderCatalog.h"
#include "RectangleGrouper.h"

class EIROBJDET_EXPORT ObjDetProcessor : public QObject
{
    Q_OBJECT
public:
    ObjDetProcessor(const cvClassifier::Type cascadeType, const Settings::Key objDetKey, QObject * parent=nullptr);
    cvClassifier::Type type() const;
    RectangleFinder *finder();
    RectangleGrouper *grouper();

    void setImage(const QQImage &inputImage);
    int findRects(const bool showMat=false, const QQRect &region=QQRect());
    int groupRects();

    QImage inputImage() const { return mInputImage; }
    QImage detectImage() const { return mGreyInputMat.toGreyImage(); }
    QQRectList rectList() const { return mRectList; }
    ObjDetResultList resultList() const { return mResultList; }

private:
    const cvClassifier::Type cmType=cvClassifier::nullType;
    const Settings::Key cmObjDetTypeKey;
    RectangleFinder * mpRectFinder=nullptr;
    RectangleGrouper * mpRectGrouper=nullptr;
    QQImage mInputImage;
    cvMat mGreyInputMat;
    QQRectList mRectList;
    ObjDetResultList mResultList;
};

