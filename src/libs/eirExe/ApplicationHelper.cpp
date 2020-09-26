// file: {repo: EIRC2}./src/libs/eirExe/ApplicationHelper.cpp
#include "ApplicationHelper.h"

#include <QTimer>

#include <APP>
#include <eirXfr/Debug.h>
#include <eirType/Milliseconds.h>
#include <eirType/VersionInfo.h>

#include "CommandLine.h"
#include "Settings.h"

#include "../../version.h"

ApplicationHelper::ApplicationHelper(QObject *parent)
    : QObject(parent)
{
    TRACEFN
    setObjectName("ApplicationHelper");
}

VersionInfo ApplicationHelper::version() const
{
    return cmVerInfo;
}

void ApplicationHelper::run()
{
    TRACEFN
    qApp->setOrganizationName(VER_ORGNAME);
    qApp->setApplicationVersion(VER_APPVER);
    QTimer::singleShot(100, this, &ApplicationHelper::initCommandLine);
}

void ApplicationHelper::initCommandLine()
{
    TRACEFN
    CMD->process();
    EMIT(commandLineInitd());
}
