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

void SimpleRectMarker::markAll(const SettingsFile::Map &markRectSettings,
                               const QQRectList &rectList)
{
    TRACEQFI << rectList.size();
    markRectSettings.dump();
    QPainter painter(this);
    QColor penColor = QColor(markRectSettings.string("PenColor","#7f00CCCC"));
    qreal penWidth = markRectSettings.real("PenWidth", 1.0);
    Qt::PenStyle penStyle = Qt::PenStyle(markRectSettings.unsignedInt("PenStyle", 1));
    QBrush penBrush(penColor);
    QPen pen(penBrush, penWidth, penStyle);
    painter.setPen(pen);
    painter.drawRects(rectList.vector());
    painter.end();
}

void SimpleRectMarker::mark(const SettingsFile::Map &markRectSettings,
                            const ObjDetResultList &resultList,
                            const ColorWheel &wheel,
                            const bool markAll)
{
    TRACEFN;
    BEXPECTNOT(wheel.isEmpty());
    markRectSettings.dump();
    resultList.dump(2);
    QPainter painter(this);
    qreal penWidth = markRectSettings.real("PenWidth", 5.0);
    Qt::PenStyle penStyle = Qt::PenStyle(markRectSettings.unsignedInt("PenStyle", 1));
    foreach (ObjDetResultItem item, resultList.list())
    {
        QBrush penBrush(wheel.at(item.quality(item.quality())));
        QPen pen(penBrush, penWidth, penStyle);
        painter.setPen(pen);
        painter.drawRect(item.resultRect());
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
