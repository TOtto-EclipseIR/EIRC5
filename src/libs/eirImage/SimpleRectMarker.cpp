#include "SimpleRectMarker.h"

#include <QBrush>
#include <QColor>
#include <QPainter>
#include <QPen>

#include <APP>
#include <eirExe/Settings.h>
#include <eirObjDet/ObjDetResultItem.h>
#include <eirObjDet/ObjDetResultList.h>
#include <eirQtCV/cvClassifier.h>
#include <eirType/QQSize.h>
#include <eirXfr/Debug.h>

SimpleRectMarker::SimpleRectMarker(const QQImage &inputImage)
    : QQImage(inputImage.convertToFormat(QImage::Format_ARGB32))
{
    TRACEQFI << inputImage << format();
}

void SimpleRectMarker::markAll(const Settings::Key &groupKey,
                               const QQRectList &rectList)
{
    TRACEQFI << rectList.size();
    int cwk = 12;
    ColorWheel cw;
    QPainter painter(this);

    STG->beginGroup(groupKey);
    cw.set(cwk, Hue::red, Hue::magenta);
//    QColor penColor = QColor(STG->string("PenColor","#CC66FFFF"));
    qreal penWidth = STG->real("PenWidth", 5.0);
    Qt::PenStyle penStyle = Qt::PenStyle(STG->unsignedInt("PenStyle", 1));
    STG->endGroup();

    QBrush penBrush;
    QPen pen(penBrush, penWidth, penStyle);
    int k = 0, n = rectList.size();
    foreach (QQRect rc, rectList)
    {
        pen.setColor(cw.at((n < cwk / 2) ? (k * cwk / n) : k));
        painter.setPen(pen);
        TRACE << k << painter.pen().color() << painter.pen().width()
                   << painter.pen().style() << rc;
        painter.drawRect(QRect(rc));
        ++k;
    }
    painter.end();
}

void SimpleRectMarker::mark(const Settings::Key &groupKey,
                            const ObjDetResultList &resultList,
                            const ColorWheel &wheel,
                            const bool markAll)
{
    TRACEFN;
    BEXPECTNOT(wheel.isEmpty());
    resultList.dump(2);
    QPainter painter(this);
    STG->beginGroup(groupKey);
    qreal penWidth = STG->real("PenWidth", 5.0);
    Qt::PenStyle penStyle = Qt::PenStyle(STG->unsignedInt("PenStyle", 1));
    STG->endGroup();
    foreach (ObjDetResultItem item, resultList.list())
    {
        QBrush penBrush(wheel.at(item.quality(item.quality())));
        QPen pen(penBrush, penWidth, penStyle);
        painter.setPen(pen);
        painter.drawRect(QRect(item.resultRect()));
        if (markAll)
        {
            QPen allPen(penBrush, 1, Qt::SolidLine);
            painter.setPen(allPen);
            painter.drawRects(item.allRects().vector());
        }
        //TODO(TitleQuality);
    }
    painter.setPen(Qt::black);
    painter.drawRects(resultList.orphanRects().vector());
    painter.end();
}

ColorWheel SimpleRectMarker::qualityWheel()
{
    TRACEFN;
    if (mQualityWheel.isEmpty())
        mQualityWheel.set(250, Hue::green, Hue::magenta);
    return mQualityWheel;
}
