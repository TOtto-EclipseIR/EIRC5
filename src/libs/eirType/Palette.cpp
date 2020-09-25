#include "Palette.h"

#include <QColor>

#include <eirXfr/Debug.h>

Palette::Palette(const int count)
{
    TRACEQFI << count;
    fill(count);
}

void Palette::setGreyScale(const int count)
{
    TRACEQFI << count;
    clear();
    for (int x = 0; x < count; ++x)
        append(QColor(x,x,x).rgb());
}

void Palette::setHeatMap()
{
    TRACEFN;
    clear();
    for (int dkg = 0; dkg < 32; ++dkg)
        append(QColor(dkg*4,dkg*4,dkg*4).rgb());
    for (int blu = 0; blu < 32; ++blu)
        append(QColor(0,0,6+blu*4).rgb());
    for (int grn = 0; grn < 32; ++grn)
        append(QColor(0,64+grn*4,0).rgb());
    for (int cyn = 0; cyn < 32; ++cyn)
        append(QColor(0,64+cyn*4,64+cyn*4).rgb());
    for (int red = 0; red < 32; ++red)
        append(QColor(64+red*4,0,0).rgb());
    for (int mag = 0; mag < 32; ++mag)
        append(QColor(64+mag*4,0,64+mag*4).rgb());
    for (int yel = 0; yel < 32; ++yel)
        append(QColor(64+yel*4,64+yel*4,0).rgb());
    for (int ltg = 0; ltg < 32; ++ltg)
        append(QColor(127+ltg*4,127+ltg*4,127+ltg*4).rgb());
    EXPECTEQ(256, size());
}
