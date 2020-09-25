#include "ColorWheel.h"

#include <eirXfr/Debug.h>

ColorWheel::ColorWheel() {;}
ColorWheel::ColorWheel(const qreal baseOpacity) : mBaseOpacity(baseOpacity) {;}

bool ColorWheel::isEmpty() const
{
    return mColorVector.isEmpty();
}

void ColorWheel::set(const int count, const Hue begin, const Hue end)
{
    qreal beginHueF = begin.toReal();
    qreal endHueF = end.toReal();
    qreal deltaHueF = beginHueF < endHueF ? endHueF - beginHueF : beginHueF + 1.0 - endHueF;
    qreal incrementF = deltaHueF / qreal(count);
    QColor baseColor;
    baseColor.setHsvF(0.0, mBaseSaturation, mBaseValue, mBaseOpacity);
    mColorVector = QQColor::Vector(count, baseColor);
    for (int k = 0; k < count; ++k)
    {
        qreal hueF = beginHueF + k * incrementF;
        QQColor color(QQColor::Hsv, (hueF < 1.0) ? hueF : hueF - 1.0,
                      mBaseSaturation, mBaseValue, mBaseOpacity);
        mColorVector[k] = color;
    }
}

void ColorWheel::setQuality(const Hue begin, const Hue end)
{
    set(250, begin, end);
}

QQColor ColorWheel::at(const int index) const
{
    return (index >= 0 && index < mColorVector.size()) ? mColorVector.at(index) : QQColor();
}

QQColor ColorWheel::quality(const int q) const
{
    return at(q/4);
}

QRgb ColorWheel::rgba(const int index)
{
    return at(index).rgba();
}
