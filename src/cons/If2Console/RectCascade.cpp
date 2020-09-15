#include "RectCascade.h"

#include <QFileInfo>

#include <eirXfr/Debug.h>

RectCascade::RectCascade(QObject *parent)
    : QObject(parent)
{
    TRACEFN;
}

bool RectCascade::load(const QFileInfo &fileInfo)
{
    mCascadeFileInfo = fileInfo;
    return load();
}

bool RectCascade::load()
{
    TRACEQFI << mCascadeFileInfo.absoluteFilePath();
    EXPECT(mCascade.load(mCascadeFileInfo
                         .absoluteFilePath().toStdString()));
    DUMPVAL(mCascade.empty());
    if (isEmpty())
    {
        close();
        return false;
    }
    DUMPVAL(mCascade.isOldFormatCascade());
    mCoreSize = QSize(32,32);
    NEEDDO(mCoreSize);
    return loaded();
}

QSize RectCascade::coreSize() const
{
    return mCoreSize;
}

void RectCascade::close()
{
    TRACEFN;
    NEEDDO(STUBBED);
//    mCascade = cvCascade();
  //  mCascadeFileInfo = QFileInfo();
    //mCoreSize = QSize();
}

bool RectCascade::isEmpty() const
{
    return mCascade.empty();
}

bool RectCascade::loaded() const
{
    return ! mCascade.empty();
}

stdRectVector RectCascade::find(
        const cvMat &inputMat,
        const qreal scaleFactor,
        const int minNeighbors,
        const cvSize minSize,
        const cvSize maxSize)
{
    TRACEQFI << scaleFactor << minNeighbors
             << minSize << maxSize;
    std::vector<cv::Rect> rects;
    DUMPVAL(loaded());
    DUMPVAL(inputMat.mat().rows);
    mCascade.detectMultiScale(inputMat.mat(),
                              rects,
                              scaleFactor,
                              minNeighbors,
                              0 /* flags unused */,
                              minSize,
                              maxSize);
    DUMPVAL(rects.size());
    return rects;
}
