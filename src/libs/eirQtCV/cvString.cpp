#include "cvString.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core/types.hpp>

cvString::cvString(const QString &qstring)
{
    assign(qstring.toStdString());
}
