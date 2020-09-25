#pragma once
#include "eirType.h"

#include <QRgb>
#include <QVector>

class EIRTYPE_EXPORT Palette : public QVector<QRgb>
{
public:
    Palette(const int count=256);
    void setGreyScale(const int count=256);
    void setHeatMap();

private:
};

