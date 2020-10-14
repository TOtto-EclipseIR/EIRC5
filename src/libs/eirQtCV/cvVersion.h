#pragma once
#include "eirQtCV.h"

#include <eirBase/Version.h>

class EIRQTCV_EXPORT cvVersion
{
public:
    cvVersion();
    int major() const               { return cmMajor; }
    int minor() const               { return cmMinor; }
    int micro() const               { return cmMicro; }
    QString string() const          { return cmString; }
    QString dottedString() const;

private:
    int cmMajor=0;
    int cmMinor=0;
    int cmMicro=0;
    QString cmString;
};

