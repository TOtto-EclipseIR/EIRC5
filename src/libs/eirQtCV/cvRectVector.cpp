#include "cvRectVector.h"

#include <eirQtCV/cvRect.h>

cvRectVector::cvRectVector() {;}

QQRectList cvRectVector::toRectList() const
{
    QQRectList rectList;
    foreach (cvRect cvrc, *this) rectList << cvrc.toRect();
    return rectList;
}
