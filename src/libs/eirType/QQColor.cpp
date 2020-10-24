#include "QQColor.h"

#include <QtDebug>

#include <eirXfr/Debug.h>

QQColor::QQColor() {;}
QQColor::QQColor(const QColor other) :  QColor(other) {;}
QQColor::QQColor(const QRgb rgb) : QColor(rgb) {;}
QQColor::QQColor(const int r, const int g, const int b, const int a) : QColor(r, g, b, a) {;}
QQColor::QQColor(const QString &namedColor) : QColor(namedColor) {;}
QQColor::QQColor(const char *namedColor) : QColor(namedColor) {;}

QQColor::QQColor(const QColor::Spec spec, const qreal f1, const qreal f2,
                                          const qreal f3, const qreal f4)
{
    TRACEQFI << spec << f1 << f2 << f3 << f4;
    switch (spec)
    {
    case Hsv:   setHsvF(f1, f2, f3, f4);         break;
    default:    MUSTDO(spec);                   break;
    }
    TRACE << toSpecString() << toString();
}

bool QQColor::isNull() const
{
    return QColor::Invalid == spec();
}

bool QQColor::isValid() const
{
    //TODO("BySpec");
    return QColor::isValid();
}

bool QQColor::notValid() const
{
    return ! isValid();
}

QString QQColor::toString() const
{
    return QColor::name(HexArgb);
}

QString QQColor::toSpecString() const
{
    int c1, c2, c3, c4;
    QString s;
    switch (spec())
    {
    case ExtendedRgb:
    case Rgb:           s = "Rgb", c1 = red(), c2 = green(), c3 = blue(), c4 = alpha();            break;
    case Hsv:           s = "Hsv", c1 = hue(), c2 = saturation(), c3 = value(), c4 = alpha();      break;
    case Hsl:           s = "Hsl", c1 = hue(), c2 = saturation(), c3 = lightness(), c4 = alpha();  break;
    case Cmyk:          s = "Cmyk", c1 = cyan(), c2 = magenta(), c3 = yellow(), c4 = black();       break;
    case Invalid:       break;
    }
    return notValid() ? "{Invalid}" : QString("%5: #%1%2%3%4")
            .arg(c1, 2, 16, QChar('0')).arg(c2, 2, 16, QChar('0'))
            .arg(c3, 2, 16, QChar('0')).arg(c4, 2, 16, QChar('0')).arg(s);
}

QDebug operator<<(QDebug dbg, const QQColor &color)
{
    dbg << color.toSpecString();
    return dbg;
}
