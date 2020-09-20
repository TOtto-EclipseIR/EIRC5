#pragma once
#include "eirQtCV.h"

#include <eirBase/Version.h>

class EIRQTCV_EXPORT cvVersion : public Version
{
public:
    cvVersion();

private:
    Version mVersion;
};

