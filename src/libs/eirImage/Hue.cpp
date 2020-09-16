#include "Hue.h"

#include <eirType/RealMath.h>

Hue Hue::white;
Hue Hue::black;
Hue Hue::red(0);
Hue Hue::blue(120);
Hue Hue::green(240);
Hue Hue::magenta(60);
Hue Hue::cyan(180);
Hue Hue::yellow(300);


Hue::Hue() {;}
Hue::Hue(const int threesixty) : Rational(threesixty, 360) {;}
Hue::Hue(const qreal tworadians) : Rational(tworadians / (2.0 * RealMath::Constants::TWO_PI), 360) {;}
Hue::Hue(const quint8 twofiftyfive) : Rational(qreal(twofiftyfive) / 255.0 * 360.0, 360) {;}

