// file: {EIRC2repo}./src/plugins/interfaces/eirIFobjdet.h
#pragma once

#include <QImage>
#include <QList>
#include <QRect>
#include <QRectF>
#include <QUrl>

class eirIFobjdet
{
protected: // virtual
    virtual bool loadResource(const QUrl &url);
    virtual bool setImage(const QImage &inputImage);
    virtual QList<QRect> findRectangles(const QRectF roi);
};
