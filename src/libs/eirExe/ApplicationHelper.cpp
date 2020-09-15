// file: {repo: EIRC2}./src/libs/eirExe/ApplicationHelper.cpp
#include "ApplicationHelper.h"

#include <QTimer>

#include <eirXfr/Debug.h>
#include <eirType/Milliseconds.h>
#include <eirType/VersionInfo.h>

//#include "ArgumentList.h"
#include "CommandLine.h"
#include "ConfigObject.h"

#include "../../version.h"

ApplicationHelper::ApplicationHelper(QObject *parent)
    : QObject(parent)
    , cmpCommandLine(new CommandLine(this))
    , cmpConfigObject(new ConfigObject(this))
    , cmpTempDir(new QTemporaryDir())
{
    TRACEFN
    setObjectName("ApplicationHelper");
    TSTALLOC(cmpTempDir);
    EXPECT(cmpTempDir->isValid())
}

VersionInfo ApplicationHelper::version() const
{
    return cmVerInfo;
}

QFile *ApplicationHelper::tempFile(const QString &ext,
                                   QObject *parent)
{
    //QString fileBaseName = Uid::create().toString();
    QString fileBaseName = Milliseconds::current()
            .toByteArray().toHex();
    QFile * f = new QFile(parent ? parent : this);
    TSTALLOC(f);
    f->setFileName(cmpTempDir->filePath(fileBaseName + ext));
    // Returning a closed, unique QFile pointer.
    // The developer can open them as the apps need,
    // but is not responsible for deleting the file.
    mTempFiles.append(f);
    return f;
}

const CommandLine *ApplicationHelper::commandLine() const
{
    return cmpCommandLine;
}

CommandLine &ApplicationHelper::rCommandLine()
{
    return *cmpCommandLine;
}

ConfigObject *ApplicationHelper::config() const
{
    return cmpConfigObject;
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
