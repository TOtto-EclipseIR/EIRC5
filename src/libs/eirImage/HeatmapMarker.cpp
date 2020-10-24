#include "HeatmapMarker.h"

#include <QBrush>
#include <QColor>
#include <QPainter>
#include <QPen>

#include <eirExe/Settings.h>
#include <eirObjDet/ObjDetResultItem.h>
#include <eirObjDet/ObjDetResultList.h>
#include <eirQtCV/cvClassifier.h>
#include <eirType/Palette.h>
#include <eirType/QQSize.h>
#include <eirXfr/Debug.h>

#include "ColorWheel.h"

HeatmapMarker::HeatmapMarker(const QQImage &inputImage)
    : QQImage(inputImage.convertToFormat(QImage::Format_ARGB32))
{
    TRACEQFI << inputImage << format();
}

void HeatmapMarker::mark(const Settings::Key &markHeatGroupKey, const ObjDetResultList &resultList)
{
    TRACEFN; UNUSED(markHeatGroupKey;)
    resultList.dump(2);

    QImage heat(size(), QImage::Format_Indexed8);
    Palette pal;
    pal.setHeatMap();
    heat.setColorTable(pal);

    foreach (ObjDetResultItem item, resultList.list())
    {
        foreach (QQRect rc, item.allRects())
        {
            for (int r = rc.top(); r < rc.bottom(); ++r)
                for (int c = rc.left(); c < rc.right(); ++c)
                {
                    quint8 p = heat.pixel(c, r);
                    p = qMin(++p, quint8(255));
                    heat.setPixel(c, r, p);
                }
        }
    }
    overlay(heat);
}

