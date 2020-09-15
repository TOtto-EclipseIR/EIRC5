#include "RectFinder.h"

#include <QImage>
#include <QPainter>

#include <eirXfr/Debug.h>

RectFinder::RectFinder(RectCascade *cascade)
    : mCascade(cascade)
{
    TRACEFN;

}

QSize RectFinder::coreSize() const
{
    return mCascade.coreSize();
}

void RectFinder::clear()
{
    mDetectMat = cvMat();
    mInputImage = QImage();
    mDetectImage = QImage();
    mRectImage = QImage();
}

bool RectFinder::loadCascade(const QFileInfo &cascadeFileInfo)
{
    mCascadeFileInfo = cascadeFileInfo;
    return loadCascade();
}


bool RectFinder::loadCascade()
{
    TRACEQFI << mCascadeFileInfo;
    return mCascade.load(mCascadeFileInfo);
}

bool RectFinder::cascadeLoaded()
{
    return mCascade.loaded();
}

bool RectFinder::loadImage(const QString &inputfileName)
{
    clear();
    mInputImage.load(inputfileName);
    mDetectImage = mInputImage
            .convertToFormat(QImage::Format_Grayscale8);
    mDetectMat.set(mDetectImage);
    EXPECT(detectLoaded());
    return detectLoaded();
}

bool RectFinder::detectLoaded()
{
    return mDetectMat.loaded();
}

QSize RectFinder::inputSize() const
{
    return QSize(mDetectMat.cols(), mDetectMat.rows());
}

int RectFinder::find(RectFinderParameters parms)
{
    TRACEFN;
    DUMPVAL(cascadeLoaded());
    DUMPVAL(detectLoaded());
    parms.calculate(inputSize());
    stdRectVector rectVector =
            mCascade.find(mDetectMat,
                             parms.scaleFactor(),
                             parms.minNeighbors(),
                             parms.minSize(),
                             parms.maxSize());
    DUMPVAL(rectVector.size());
    return fillRectList(rectVector);
}

QImage RectFinder::inputImage(const QImage::Format format)
{
    if ( ! mInputImage.isNull())
        return mInputImage.convertToFormat(format);

    NEEDDO(it); NEEDUSE(format); NEEDDO(return);

    return QImage();
}

QImage RectFinder::detectImage(const QImage::Format format)
{
    if ( ! mDetectImage.isNull())
        return mDetectImage.convertToFormat(format);
    mDetectImage = mDetectMat.toImage(QImage::Format_Grayscale8, "jpg");
    return mDetectImage;
}

cvMat RectFinder::detectMat() const
{
    return mDetectMat;
}

QImage RectFinder::rectImage(const QPen pen,
                             const QImage::Format format)
{
    if ( ! mRectImage.isNull())    return mRectImage.convertToFormat(format);

    QImage rectImage = detectImage()
            .convertToFormat(format);
    QPainter painter;
    painter.begin(&rectImage);
    painter.setPen(pen);
    foreach (QRect rc, rectList())
    {
        painter.drawRect(rc);
    }
    NEEDDO(rectList);
    painter.end();
    return mRectImage = rectImage
            ;
}

RectList RectFinder::rectList() const
{
    return mRectList;
}

int RectFinder::fillRectList(const stdRectVector &cvVector)
{
    WANTDO(Move to rectCascade);
    mRectList.clear();
    foreach (cvRect cvrc, cvVector)
        mRectList.append(QRect(cvrc));
    return mRectList.size();
}

