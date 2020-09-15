#pragma once

#include <QFileInfo>
#include <QImage>
#include <QList>
#include <QPen>
#include <QRect>

#include "cvMat.h"
#include "cvRect.h"
#include "RectCascade.h"
#include "RectFinderParameters.h"

typedef QList<QRect> RectList;

class RectFinder
{
public:
    RectFinder(RectCascade *cascade=nullptr);
    QSize coreSize() const;
    void clear();
    bool loadCascade(const QFileInfo &cascadeFileInfo);
    bool loadCascade();
    bool cascadeLoaded();
    bool loadImage(const QString &inputfileName);
    bool detectLoaded();
    QSize inputSize() const;
    int find(RectFinderParameters parms);
    QImage inputImage(const QImage::Format format=QImage::Format_RGB32);
    QImage detectImage(const QImage::Format format=QImage::Format_Grayscale8);
    cvMat detectMat() const;
    QImage rectImage(const QPen pen=QPen(QBrush(Qt::blue), 1),
                     const QImage::Format format=QImage::Format_RGB32);
    cvRect::Vector cvRectVector() const;
    RectList rectList() const;

protected:
    int fillRectList(const stdRectVector & cvVector);

private:
    QFileInfo mCascadeFileInfo;
    RectCascade mCascade;
//    cvMat mInputMat;
    cvMat mDetectMat;
    QImage mInputImage;
    QImage mDetectImage;
    QImage mRectImage;
    RectList mRectList;
};

