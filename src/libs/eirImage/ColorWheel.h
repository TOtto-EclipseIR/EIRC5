#pragma once
#include "eirImage.h"

#include <QMetaType>

#include <eirBase/Typedefs.h>
#include <eirType/QQColor.h>

#include "Hue.h"

class EIRIMAGE_EXPORT ColorWheel
{
public:
    ColorWheel();
    ColorWheel(const qreal baseOpacity);
    ColorWheel(const qreal baseSaturation, const qreal baseValue);
    ColorWheel(const qreal baseOpacity, const qreal baseSaturation, const qreal baseValue);
    bool isEmpty() const;
    void set(const int count, const Hue begin, const Hue end);
    QQColor at(const int index) const;
    QRgb rgba(const int index);

private:
    qreal mBaseOpacity=1.0;
    qreal mBaseSaturation=1.0;
    qreal mBaseValue=1.0;
    QQColor::Vector mColorVector;
};
Q_DECLARE_METATYPE(ColorWheel)
