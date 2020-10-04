#pragma once
#include "eirObjDet.h"

#include <eirExe/Settings.h>
#include <eirQtCV/cvCascade.h>
#include <eirQtCV/cvMat.h>
#include <eirType/QQImage.h>
#include <eirType/QQRectList.h>

#include "ObjDetResultList.h"
#include "ObjDetGroupSettings.h"
#include "ObjDetRectSettings.h"

class EIROBJDET_EXPORT ObjDetProcessor
{
public:
    ObjDetProcessor(const cvCascadeType cascadeType);
    cvCascadeType type() const;
    cvCascade * cascade();

    void configure(const Settings::Key rectKey, const Settings::Key groupKey);
    void setImage(const QQImage &inputImage);
    int findRects(const QQRect &region=QQRect());
    int groupRects();

    ObjDetRectSettings rectSettings() const { return mRectSettings; }
    ObjDetGroupSettings groupSettings() const { return mGroupSettings; }
    QImage inputImage() const { return mInputImage; }
    QImage detectImage() const { return mGreyInputMat.toGreyImage(); }
    QQRectList rectList() const { return mRectList; }
    ObjDetResultList resultList() const { return mResultList; }

private:
    const cvCascadeType cmType=cvCascadeType::nullType;
    cvCascade * mpCascade=nullptr;
    ObjDetRectSettings mRectSettings;
    ObjDetGroupSettings mGroupSettings;
    QQImage mInputImage;
    cvMat mGreyInputMat;
    QQRectList mRectList;
    ObjDetResultList mResultList;
};

