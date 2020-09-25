// file: {repo: EIRC2}./src/libs/eirExe/ApplicationHelper.cpp
#include "ApplicationHelper.h"

#include <QTimer>

#include <eirXfr/Debug.h>
#include <eirType/Milliseconds.h>
#include <eirType/VersionInfo.h>

#include "CommandLine.h"
#include "SettingsFile.h"

#include "../../version.h"

ApplicationHelper::ApplicationHelper(QObject *parent)
    : QObject(parent)
    , cmpTempDir(new QTemporaryDir())
    , cmpCommandLine(new CommandLine(this))
    , cmpSettings(new SettingsFile(this))
{
    TRACEFN
    setObjectName("ApplicationHelper");
    TSTALLOC(cmpCommandLine);
    TSTALLOC(cmpSettings);
    TSTALLOC(cmpTempDir);
    cmpCommandLine->setObjectName("ApplicationHelper::CommandLine");
    cmpSettings->setObjectName("ApplicationHelper::Settings");
    EXPECT(cmpTempDir->isValid())
}

VersionInfo ApplicationHelper::version() const
{
    return cmVerInfo;
}

QFile *ApplicationHelper::tempDirFile(const QString &ext,
                                   QObject *parent)
{
    TRACEQFI << ext << QOBJNAME(parent);
    QString fileBaseName = Milliseconds::current()
            .toByteArray().toHex();
    QFile * f = new QFile(parent ? parent : this);
    TSTALLOC(f);
    f->setFileName(cmpTempDir->filePath(fileBaseName + "." + ext));
    // Returning a closed, unique QFile pointer.
    // The developer can open them as the apps need,
    // but is not responsible for deleting the file.
    return f;
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

SettingsFile *ApplicationHelper::settings() const
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
