#include "cvRect.h"

#include <eirType/QQPoint.h>
#include <eirType/QQSize.h>

#include "cvSize.h"

cvRect::cvRect() : cv::Rect() {;}
cvRect::cvRect(const QRect qrc)
    : cv::Rect(qrc.left(), qrc.top(), qrc.width(), qrc.height()) {;}
cvRect::cvRect(const cv::Rect cvrc) : cv::Rect(cvrc) {;}
cvRect::cvRect(const int left, const int top, const int width, const int height)
    : cv::Rect(left, top, width, height) {;}

QQRect cvRect::toRect() const
{
    return QQRect(QQSize(width, height), QQPoint(x + width/2, y + height/2));
}

