#include "SimpleRectMarker.h"

#include <QBrush>
#include <QColor>
#include <QPainter>
#include <QPen>

#include <eirObjDet/ObjectDetector.h>
#include <eirObjDet/ObjDetResultItem.h>
#include <eirObjDet/ObjDetResultList.h>
#include <eirQtCV/cvCascade.h>
#include <eirType/QQSize.h>
#include <eirXfr/Debug.h>

SimpleRectMarker::SimpleRectMarker(const QQImage &inputImage)
    : QQImage(inputImage.convertToFormat(QImage::Format_ARGB32))
{
    TRACEQFI << inputImage << format();
}

void SimpleRectMarker::markAll(const Configuration &markRectConfig,
                               const QQRectList &rectList)
{
    TRACEQFI << rectList.size();
    markRectConfig.dump();
    QPainter painter(this);
    QColor penColor = QColor(markRectConfig.string("PenColor","#7f00CCCC"));
    qreal penWidth = markRectConfig.real("PenWidth", 1.0);
    Qt::PenStyle penStyle = Qt::PenStyle(markRectConfig.unsignedInt("PenStyle", 1));
    QBrush penBrush(penColor);
    QPen pen(penBrush, penWidth, penStyle);
    painter.setPen(pen);
    painter.drawRects(rectList.vector());
    painter.end();
}

void SimpleRectMarker::mark(const Configuration &markRectConfig,
                            const ObjDetResultList &resultList,
                            const ObjDetPak &pak)
{
    TRACEQFI << pak;
    markRectConfig.dump();
    //ObjDetResultList resultList;
    //resultList.set(pak.at("PreScan/Results"));
    resultList.dump(1);
    QPainter painter(this);

#if 1
    QColor penColor = QColor(markRectConfig.string("PenColor","#7f00CCCC"));
#else
    QColor penColor;
    qreal hue = 0.0;
    qreal hueRotate = 1.0 / qBound(1.0, qreal(resultList.count()), 12.0);
    penColor.setHslF(hue, 1.0, 0.5, 0.25);
#endif
    qreal penWidth = markRectConfig.real("PenWidth", 5.0);
    Qt::PenStyle penStyle = Qt::PenStyle(markRectConfig.unsignedInt("PenStyle", 1));
    foreach (ObjDetResultItem item, resultList.list())
    {
        item.dump();
#if 1
        int qual = item.quality(500);
        QColor qualColor = penColor.lighter(qual / 5);
        QBrush penBrush(qualColor);
#else
        hue += hueRotate;
        if (hue > 1.0) hue -= 1.0;
        penColor.setHslF(hue, 1.0, 0.5, 0.25);
        QBrush penBrush(penColor);
#endif
        QPen pen(penBrush, penWidth, penStyle);
        painter.setPen(pen);
        painter.drawRect(item.resultRect());
        QPen allPen(penBrush, 1, Qt::SolidLine);
        painter.setPen(allPen);
        painter.drawRects(item.allRects().vector());
        TODO(TitleQuality);
    }
    painter.setPen(Qt::black);
    painter.drawRects(resultList.orphanRects().vector());

    QColor sizeColor = QColor(markRectConfig.string("SizePenColor","#FFFF0000"));
    QPen sizePen(sizeColor);
    painter.setPen(sizePen);
    QQSize coreSize = pak.at("PreScan/CoreSize").toSize();
    int x = 16;
    painter.drawLine(x, 16, x, 24);
    x += coreSize.width();
    painter.drawLine(x, 16, x, 24);
    QVariant parmVari = pak.at("PreScan/Parameters");
    cvCascade::Parameters parms(parmVari);
    DUMP << parmVari;
    DUMP << parms.dumpList();
    qreal width = qreal(parms.minSize().width());
    qreal maxW  = qreal(parms.maxSize().width());
    qreal factor = parms.factor();
    TRACEQFI << width << maxW << factor;
    BEXPECTNOT(qIsNull(width));
    while (width < maxW)
    {
        x += width;
        painter.drawLine(x, 16, x, 24);
        width *= factor;
    }
    TRACEQFI << width << maxW << factor;
    painter.end();
}
