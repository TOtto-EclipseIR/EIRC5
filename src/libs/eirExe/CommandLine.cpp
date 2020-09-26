// file: {EIRC2 repo}/./src/libs/eirExe/CommandLine.cpp
#include "CommandLine.h"

#include <QCoreApplication>
#include <QDir>
#include <QTimer>

#include <APP>
#include <eirXfr/Debug.h>
#include <eirType/QQFileInfo.h>
#include <eirType/QQFileInfoList.h>
#include <eirType/QQString.h>

#include "CommandLineClientInterface.h"

CommandLine::CommandLine(QObject *parent)
    : QObject(parent)
    , cmExeArgumentList(QCoreApplication::arguments())
{
    TRACEFN
    setObjectName("CommandLine");
    EMIT(constructed());
}

void CommandLine::set(CommandLineClientInterface *interface)
{
    TRACEFN
            mpInterface = interface;
}

CommandLine::ExpandDirResultList CommandLine::expandDirResults() const
{
    return mExpandDirResultList;
}

int CommandLine::positionalArgumentSize() const
{
    return positionalArgumentList().size();
}

QStringList CommandLine::positionalArgumentList() const
{
    return mPositionalArgumentList;
}

QString CommandLine::firstPositionalArgument() const
{
    return positionalArgumentSize()
            ? mPositionalArgumentList.first() : QString();
}

QString CommandLine::takePositionalArgument()
{
    TRACEQFI << firstPositionalArgument();
    if (positionalArgumentSize())
        ++mPositionalArgumentsTaken;
    return positionalArgumentSize()
            ? mPositionalArgumentList.takeFirst() : QString();
}

int CommandLine::takePositionalArgumentCount() const
{
    TRACEQFI << mPositionalArgumentsTaken;
    return mPositionalArgumentsTaken;
}

/*
QQFileInfoList CommandLine::positionalFileInfoList() const
{
    return mPositionalFileDirInfoList;
}
*/
const QStringList CommandLine::exeArguments(bool withNumbers) const
{
    QStringList argList = cmExeArgumentList;
    if (withNumbers)
        for (int x = 0; x < argList.size(); ++x)
            argList[x].prepend(QString("%1. ").arg(x,3));
    return argList;
}

const QQFileInfo CommandLine::exeFileInfo() const
{
    return mExeFileInfo;
}

void CommandLine::process()
{
    TRACEQFI << "ExeArgs:" << cmExeArgumentList;
    QStringList arguments;
    mExeFileInfo = QQFileInfo(QQString(cmExeArgumentList.first()));
    arguments = expandFileArguments(cmExeArgumentList.mid(1), '@');
    TRACE << "Expanded:" << arguments;
    arguments = stripSettings(arguments);
    TRACE << "Settings:";
    DUMP << STG->toStringList();
    TRACE << "Post Configuration:" << arguments;
    arguments = extractDirectiveArguments(arguments);
    TRACE << "Post Extract:" << arguments;
    if (mpInterface) arguments = parseQtOptions(arguments);
    TRACE << "virtual setup() complete";

    mPositionalArgumentList = arguments;
    TRACE << "PosArgs:" << mPositionalArgumentList;
    dump();
} // process()

void CommandLine::expandDirectories(const int recurseDepth)
{
    TRACEQFI << "recurseDepth:" << recurseDepth;
    dumpPositionalArgs();
    WANTUSE(recurseDepth)
    WARN << "Only recurseDepth=1 for  now";

    QStringList expandedArgs;
    foreach (QString argIn, mPositionalArgumentList)
    {
        if (QQFileInfo::tryIsFile(argIn))
        {
            expandedArgs << argIn;
        }
        else if (QQFileInfo::tryIsDir(argIn))
        {
            QDir dir(argIn);
            QStringList fileNames
                = dir.entryList(QDir::Files, QDir::NoSort);
            if ( ! fileNames.isEmpty())
            {
                ExpandDirResult edr;
                edr.dir = dir;
                edr.firstFileName = fileNames.first();
                edr.fileCount = fileNames.size();
                mExpandDirResultList << edr;
            }
            foreach (QString fileName, fileNames)
            {
                QFileInfo fi(dir, fileName);
                expandedArgs << fi.absoluteFilePath();
            }
        }
        else
        {
            WARN << argIn << "not file or dir";
        }
    }
    mPositionalArgumentList = expandedArgs;
    TRACEQFI << "Output Files:";
    dumpPositionalArgs();
}

void CommandLine::dump()
{
    DUMP << ">>>CommandLine:";
    DUMP << "===exeArgumentList:";
    foreach (QString exeArg, cmExeArgumentList)
        DUMP << "  " << exeArg;
    DUMP << "---exeFileInfo:" << mExeFileInfo;
    DUMP << "---positionalArgumentList:";
    dumpPositionalArgs();
    DUMP << "---Settings:";
    STG->dump();
}


QStringList CommandLine::expandFileArguments(const QStringList arguments,
                                             const QChar trigger)
{
    TRACEQFI << arguments;
    QStringList expanded;
    foreach (QQString arg, arguments)
    {
        if (arg.startsWith(trigger))
        {
            QQFileInfo argFileInfo(arg.mid(1), QQString::NoFlag);
            TRACE << "Expanding" << argFileInfo.absoluteFilePath();
            TEXPECT(argFileInfo.exists());
            TEXPECT(argFileInfo.isReadable());
            TEXPECT(argFileInfo.isFile());
            expanded << readTxtFileArguments(argFileInfo);
        }
        else
        {
            expanded << arg;
        }
        TRACE << expanded;
    }
    return expanded;
}

QStringList CommandLine::extractDirectiveArguments(
        const QStringList &currentArgs)
{
    TRACEQFI << currentArgs;
    TODO(it)
    return currentArgs;
}

QStringList CommandLine::parseQtOptions(
        const QStringList &currentArgs)
{
    QCommandLineParser parser;
    if (mpInterface) mpInterface->setup(&parser);
    NEEDDO(Extract from parser)
    return currentArgs;
}

QStringList CommandLine::stripSettings(
        const QStringList &expandedArgs,
        const Settings::Key &prefix,
        const QChar &trigger)
{
    TRACEQFI << expandedArgs << prefix() << trigger;
    QStringList remainingArgs;
    foreach (QString arg, expandedArgs)
        if (arg.startsWith(trigger))
            parseSettingArgument(arg, prefix);
        else
            remainingArgs << arg;
    TRACEQFI << remainingArgs;
    return remainingArgs;
}


void CommandLine::parseSettingArgument(const QString &arg,
                                      const Settings::Key &prefix)
{
    TRACEQFI << arg << prefix();
    QStringList qsl = arg.split('=');
    Settings::Key key = qsl[0].mid(1);
    key.prependName(prefix);
    Settings::Value valu = (qsl.size() > 1) ? qsl[1] : "true";
    STG->set(key, valu);
    TRACE << key() << "=" << valu;
}
QStringList CommandLine::readTxtFileArguments(const QFileInfo &argFileInfo)

{
    TRACEQFI << argFileInfo.absoluteFilePath();
    QStringList newArgs;
    QFile file(argFileInfo.absoluteFilePath(), this);
    WEXPECT(file.open(QIODevice::ReadOnly | QIODevice::Text))
    WEXPECT(file.exists() && file.isReadable())
    while ( ! file.atEnd())
    {
        QByteArray fileLine = file.readLine().simplified();
        //TRACE << "fileLine: {>" << fileLine << "<}";
        if (fileLine.isEmpty() || fileLine.startsWith('#'))
            continue;
        newArgs << fileLine;
    }
    TRACE << file.fileName() << "newArgs" << newArgs;
    return newArgs;
}

void CommandLine::dumpPositionalArgs() const
{
    int nArgs = mPositionalArgumentList.size();
    DUMP << "eirExe : CommandLine PositionalArgs n=" << nArgs;
    for (int index=0; index < nArgs; ++index)
        DUMP << "  " << index << mPositionalArgumentList[index];
}

