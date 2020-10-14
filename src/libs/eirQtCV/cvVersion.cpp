#include "cvVersion.h"

#include <QString>

#include <opencv2/core/version.hpp>

cvVersion::cvVersion()
    : cmMajor(CV_VERSION_MAJOR)
    , cmMinor(CV_VERSION_MINOR)
    , cmMicro(CV_VERSION_REVISION)
    , cmString(CV_VERSION) {;}

QString cvVersion::dottedString() const
{
    return QString("%1.%2.%3").arg(cmMajor).arg(cmMinor).arg(cmMicro);
}
