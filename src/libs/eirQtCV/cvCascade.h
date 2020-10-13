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

public:
    cvCascade(const Type &type);
    QQRectList detectRectangles(const cvMat greyMat, const Parameters &parms,
                         const bool showDetect=false, const QQRect &region=QQRect()) const;



private:
    Type cmType=nullType;
};
