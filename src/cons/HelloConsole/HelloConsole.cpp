#include "HelloConsole.h"

#include <eirExe/CommandLine.h>
#include <eirXfr/Debug.h>
#include <eirXfr/StartupDebug.h>
Q_GLOBAL_STATIC(StartupDebug, sdo)

HelloConsole::HelloConsole(QObject *parent)
    : Console(parent)
{
    sdo->start(qApp->arguments().first(), "./log");
    setObjectName("HelloConsole");
    TRACEQFI << QOBJNAME(this);
    CONNECT(this, &HelloConsole::constructed,
            this, &ApplicationHelper::run);
    CONNECT(this, &ApplicationHelper::commandLineInitd,
            this, &HelloConsole::start);
    EMIT(constructed());
}

void HelloConsole::start()
{
    TRACEFN;
    CONNECT(this, &HelloConsole::started,
            this, &HelloConsole::tellSystem);
    CONNECT(this, &HelloConsole::systemTold,
            this, &HelloConsole::finish);
    CONNECT(this, &HelloConsole::finished,
            qApp, &QCoreApplication::quit);
    EMIT(started());
}

void HelloConsole::tellSystem()
{
    TRACEFN;
    writeLine("Hello Console started "+baseDateTime().toString());
    writeLine(CMD->exeFileInfo().absoluteFilePath());
    writeLine("Command Line Arguments:");
    writeLines(CMD->exeArguments(true));

    EMIT(systemTold());
}

void HelloConsole::finish()
{
    TRACEFN;
    EMIT(finished());
}
