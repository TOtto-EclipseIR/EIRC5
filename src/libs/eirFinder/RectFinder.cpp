#include "RectFinder.h"

#include <QPainter>

#include <eirXfr/Debug.h>

RectFinder::RectFinder(ConfigObject *cfgObj,
                       QObject *parent)
{
    TRACEQFI << QOBJNAME(cfgObj) << QOBJNAME(parent);
    mpConfigObject = cfgObj;
    mFinderCascadeList.reserve(CascadeType::sizeCascadeType);
    for (int x = 0; x < CascadeType::sizeCascadeType; ++x)
        mFinderCascadeList.append(FinderCascade(CascadeType(x),
                                                mpConfigObject));
}

void RectFinder::set(ConfigObject *cfgObj)
{
    mpConfigObject = cfgObj;
}

void RectFinder::set(const QDir &baseCascadeDir)
{
    TRACEQFI << baseCascadeDir << baseCascadeDir.exists() << baseCascadeDir.isReadable();
    mBaseCascadeDir = baseCascadeDir;
}

FinderCascade &RectFinder::finderCascade(const CascadeType &cascadeType)
{
    return mFinderCascadeList[cascadeType];
}

FinderCascade RectFinder::finderCascade(const CascadeType &cascadeType) const
{
    return mFinderCascadeList.at(cascadeType);
}

bool RectFinder::loaded(const CascadeType &cascadeType) const
{
    TRACEQFI << cascadeType() << cascadeType.name();
    cvCascade * pcvc = finderCascade(cascadeType).cascade();
    TSTALLOC(pcvc);
    return pcvc->isLoaded();
}

QImage RectFinder::findRectImage(const CascadeType &cascadeType) const
{
    TRACEQFI << cascadeType();
    return finderCascade(cascadeType).findRectImage();
}

QList<QRect> RectFinder::rectangleList(const CascadeType &cascadeType)
{
    TRACEQFI << finderCascade(cascadeType).rectList().size();
    return finderCascade(cascadeType).rectList();
}

QImage RectFinder::makeRectImage(const CascadeType &cascadeType, bool all)
{
    TRACEQFI << cascadeType.name() << all;
        QImage rectImage = findRectImage(cascadeType);
    QPainter painter;
    painter.begin(&rectImage);
    painter.setPen(Qt::blue);
    QBrush brush(Qt::blue);
    QPen pen(brush, all ? 1 : 3);
    painter.setPen(pen);
    foreach (QRect rc, rectangleList(cascadeType))
        painter.drawRect(rc);
    painter.end();
    TRACERTN(rectImage);
    return rectImage;
}

void RectFinder::load(const CascadeType &cascadeType,
                      const QFileInfo &xmlFileInfo)
{
    TRACEQFI << cascadeType() << xmlFileInfo;
    cvCascade * pcvc = cascade(cascadeType);
    TSTALLOC(pcvc);
    TRACE << xmlFileInfo << xmlFileInfo.exists()
          << xmlFileInfo.isReadable() << xmlFileInfo.isFile();
    WEXPECT(xmlFileInfo.exists());
    WEXPECT(xmlFileInfo.isReadable());
    WEXPECT(xmlFileInfo.isFile());
    WEXPECT(xmlFileInfo.isFile());
    EXPECT(pcvc->loadCascade(xmlFileInfo.filePath()));
}

void RectFinder::set(const CascadeType &cascadeType,
                     const QImage &image)
{
    TRACEQFI << cascadeType() << image.size() << image.format();
    finderCascade(cascadeType).setImage(image);
    TRACERTV();
}

void RectFinder::findRectangles(const CascadeType &cascadeType)
{
    TRACEQFI << cascadeType();
    finderCascade(cascadeType).findRectangles();
}

// private
cvCascade *RectFinder::cascade(const CascadeType &cascadeType) const
{
    return finderCascade(cascadeType).cascade();
}
