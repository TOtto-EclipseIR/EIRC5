// file: {repo: EIRC2}./src/libs/eirExe/ApplicationHelper.cpp
#include "ApplicationHelper.h"

#include <QTimer>

#include <eirXfr/Debug.h>
#include <eirType/Milliseconds.h>
#include <eirType/VersionInfo.h>

#include "CommandLine.h"
#include "Settings.h"

#include "../../version.h"

ApplicationHelper::ApplicationHelper(QObject *parent)
    : QObject(parent)
    , cmpCommandLine(new CommandLine(this))
    , cmpSettings(new Settings(this))
{
    TRACEFN
    setObjectName("ApplicationHelper");
    TSTALLOC(cmpCommandLine);
    TSTALLOC(cmpSettings);
    cmpCommandLine->setObjectName("ApplicationHelper::CommandLine");
    cmpSettings->setObjectName("ApplicationHelper::Settings");
}

VersionInfo ApplicationHelper::version() const
{
    return cmVerInfo;
}

const CommandLine *ApplicationHelper::commandLine() const
{
    TSTALLOC(cmpCommandLine);
    return cmpCommandLine;
}

CommandLine &ApplicationHelper::rCommandLine()
{
    TSTALLOC(cmpCommandLine);
    return *cmpCommandLine;
}

Settings *ApplicationHelper::settings() const
{
    TSTALLOC(cmpSettings);
    return cmpSettings;
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
    TSTALLOC(cmpCommandLine)
    cmpCommandLine->process();
    EMIT(commandLineInitd());
}
