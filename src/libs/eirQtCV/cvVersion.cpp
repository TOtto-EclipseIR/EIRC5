#include "cvVersion.h"

#include <QString>

#include <opencv2/core/version.hpp>

cvVersion::cvVersion()
{
    mVersion.setMajor(CV_VERSION_MAJOR);
    mVersion.setMinor(CV_VERSION_MINOR);
    mVersion.setMini(CV_VERSION_REVISION);
    mVersion.setString(CV_VERSION);
}
