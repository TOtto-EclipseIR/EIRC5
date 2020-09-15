// file: {EIRC2repo}./src/plugins/interfaces/eirIFrectdet.h
#pragma once

#include <QImage>
#include <QList>
#include <QRect>
#include <QRectF>
#include <QUrl>

class eirIFrectdet
{
protected: // virtual
    virtual bool loadResource(const QUrl &url);
    virtual bool configure(const QVariantMap &configuration);
    virtual bool setImage(const QImage &inputImage);
    virtual QList<QRect> findRectangles(const QRectF roi);
};
