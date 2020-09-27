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
    TRACEQFI << QOBJNAME(parent);
    setObjectName("ApplicationHelper");
}

ApplicationHelper::ApplicationHelper(const Flags flags, QObject *parent)
    : QObject(parent)
    , cmFlags(flags)
{
    TRACEQFI << flags << QOBJNAME(parent);
    setObjectName("ApplicationHelper");
}

VersionInfo ApplicationHelper::version() const
{
    return cmVerInfo;
}

QStringList ApplicationHelper::arguments() const
{
    return qApp->arguments();
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
    CMD->process(cmFlags & ExpandCommandLineDirs);
    EMIT(commandLineInitd());
}
