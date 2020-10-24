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
    bool isEmpty() const        { return mColorVector.isEmpty(); }
    int size() const            { return mColorVector.size(); }
    void set(const int count, const Hue begin, const Hue end);
    void setQuality(const Hue begin, const Hue end);
    QQColor at(const unsigned index, const unsigned count=0) const;
    QQColor quality(const int q) const;
    QRgb rgba(const int index);

private:
    qreal mBaseOpacity=0.5;
    qreal mBaseSaturation=0.5;
    qreal mBaseValue=0.5;
    QQColor::Vector mColorVector;
};
Q_DECLARE_METATYPE(ColorWheel)
