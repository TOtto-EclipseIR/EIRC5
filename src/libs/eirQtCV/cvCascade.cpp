#include "cvCascade.h"

#include <QDomElement>
#include <QColor>
#include <QTextStream>
#include <QDomElement>
#include <QPainter>
#include <QPixmap>

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/core/types.hpp>

#include <eirExe/XmlFile.h>
#include <eirXfr/Debug.h>

#include "cvRect.h"
#include "cvRectVector.h"
#include "cvString.h"

cvCascade::cvCascade(const cvCascade::Type &type)
    : cmType(type)
{
    TRACEQFI << type;
    TODO(cv::redirectError);
}

cvCascade::Type cvCascade::type() const
{
    return cmType;
}

BasicName cvCascade::typeName() const
{
    return typeName(cmType);
}


