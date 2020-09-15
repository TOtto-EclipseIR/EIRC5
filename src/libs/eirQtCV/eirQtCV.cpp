#include "eirQtCV.h"

#include <QString>

#include <opencv2/opencv.hpp>

eirQtCV::eirQtCV()
{
}

// static
QString eirQtCV::cvVersion()
{
    return CV_VERSION;
}
