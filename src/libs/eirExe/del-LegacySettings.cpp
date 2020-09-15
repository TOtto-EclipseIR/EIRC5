// file: {repo: EIRC2}./src/libs/eirExe/Settings.cpp
#include "del-LegacySettings.h"

#include <QTimer>

#include <eirXfr/Debug.h>

#include "ApplicationHelper.h"

LegacySettings::LegacySettings(ApplicationHelper *parent)
    : QSettings(parent)
    , mpHelper(parent)
{
    TRACEFN
    setObjectName("Settings");
}

ApplicationHelper * LegacySettings::helper()
{
    return mpHelper;
}
