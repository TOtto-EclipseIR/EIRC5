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

QQStringList CommandLine::positionalArgumentList() const
{
    return mPositionalArgumentList;
}

QQString CommandLine::firstPositionalArgument() const
{
    return positionalArgumentSize()
            ? mPositionalArgumentList.first() : QQString();
}

QQString CommandLine::takePositionalArgument()
{
    TRACEQFI << firstPositionalArgument();
    if (positionalArgumentSize())
        ++mPositionalArgumentsTaken;
    return positionalArgumentSize()
            ? mPositionalArgumentList.takeFirst() : QString();
}

int CommandLine::positionalArgumentsTaken() const
{
    TRACEQFI << mPositionalArgumentsTaken;
    return mPositionalArgumentsTaken;
}

const QQStringList CommandLine::exeArguments(bool withNumbers) const
{
    QQStringList argList = cmExeArgumentList;
    if (withNumbers)
        for (int x = 0; x < argList.size(); ++x)
            argList[x].prepend(QString("%1. ").arg(x,3));
    return argList;
}

const QQFileInfo CommandLine::exeFileInfo() const
{
    return mExeFileInfo;
}

void CommandLine::process(const bool expandDirs)
{
    TRACEQFI << "ExeArgs:" << cmExeArgumentList;
    mRemainingArgumentList = cmExeArgumentList;
    mExeFileInfo = QQFileInfo(QQString(mRemainingArgumentList.takeFirst()));

    if (mpInterface) parseQtOptions();
    extractDirectiveArguments();

    stripSettings();
    TRACE << "Settings:";
    DUMP << STG->toStringList();
    TRACE << "Post Settings:" << mRemainingArgumentList;
    if (expandDirs) expandDirectories();
    TRACE << "Expanded:" << mRemainingArgumentList;
    mPositionalArgumentList = mRemainingArgumentList;
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
                QQFileInfo fi(dir, fileName);
                expandedArgs << fi.absoluteFilePath();
            }
        }
        else
        {
            WARN << argIn << "not file or dir";
            EMIT(warning(argIn, "Not Recognized"));
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
    foreach (QString exeArg, cmExeArgumentList) DUMP << "  " << exeArg;
    DUMP << "---exeFileInfo:" << mExeFileInfo;
    DUMP << "---positionalArgumentList:";
    dumpPositionalArgs();
    DUMP << "---Settings:";
    STG->dump();
}


void CommandLine::expandFileArguments(const QChar trigger)
{
    TRACEQFI << trigger;
    foreach (QQString arg, mRemainingArgumentList)
    {
        if (arg.startsWith(trigger))
        {
            QQFileInfo argFileInfo(arg.mid(1), QQString::NoFlag);
            TRACE << "Expanding" << argFileInfo.absoluteFilePath() << argFileInfo.attributes();
            WEXPECT(argFileInfo.exists());
            WEXPECT(argFileInfo.isReadable());
            WEXPECT(argFileInfo.isFile());
            if (argFileInfo.tryIsFile())
            {
                QQStringList expanded = readTxtFileArguments(argFileInfo);
                TRACE << expanded;
                mRemainingArgumentList.prepend(expanded);
            }
        }
    }
}

void CommandLine::extractDirectiveArguments()
{
    TRACEFN;
    TODO(it)
}

void CommandLine::parseQtOptions()
{
    TRACEFN;
    QCommandLineParser parser;
    if (mpInterface) mpInterface->setup(&parser);
    NEEDDO(Extract from parser)
}

void CommandLine::stripSettings(const Settings::Key &prefix, const QChar &trigger)
{
    TRACEQFI << prefix() << trigger;
    QStringList remainingArgs;
    foreach (QString arg, mRemainingArgumentList)
        if (arg.startsWith(trigger))
        {
            parseSettingArgument(arg, prefix);
            mRemainingArgumentList.removeOne(arg);
        }
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

QQStringList CommandLine::readTxtFileArguments(const QQFileInfo &argFileInfo)
{
    TRACEQFI << argFileInfo.absoluteFilePath() << argFileInfo.attributes();
    QQStringList newArgs;
    QFile file(argFileInfo.absoluteFilePath(), this);
    EXPECT(file.open(QIODevice::ReadOnly | QIODevice::Text));
    if ( ! file.isReadable())
        EMIT(warning(file.fileName() + " "
                     + argFileInfo.attributes(), "Not a Readable File"));

    while ( ! file.atEnd())
    {
        QByteArray fileLine = file.readLine().simplified();
        TRACE << "fileLine: {>" << fileLine << "<}";
        if (fileLine.isEmpty() || fileLine.startsWith('#'))
            continue;
        newArgs << QQString(fileLine);
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

