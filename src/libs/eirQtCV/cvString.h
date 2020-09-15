#pragma once
#include "eirQtCV.h"

#include <QString>

class EIRQTCV_EXPORT cvString : public std::string
{
public:
    cvString(const QString &qstring);
};

