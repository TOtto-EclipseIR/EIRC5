#include "FaceConsole.h"

#include <QDateTime>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QTimer>

#include <eirExe/CommandLine.h>
#include <eirExe/ConfigObject.h>
//#include <eirFinder/CascadeType.h>
#include <eirType/Success.h>
#include <eirXfr/Debug.h>
#include <eirXfr/StartupDebug.h>
//#include <eirImageIO/BaseOutputDir.h>
//#include <eirImageIO/OutputManager.h>

//#include <eirRectFind/RectFinder.h>
//#include <eirMarker/MarkerManager.h>

FaceConsole::FaceConsole(QObject *parent)
    : Console(parent)
    , cmpConfigObject(new ConfigObject(parent))
{
    TRACEFN;
    setObjectName("FaceConsole");
    TSTALLOC(cmpConfigObject);

    QTimer::singleShot(500, this, &FaceConsole::initializeApplication);
    TRACERTV();
}

ConfigObject *FaceConsole::config() const
{
    return cmpConfigObject;
}

void FaceConsole::initializeApplication()
{
    TRACEFN;
    QLocale locale;
    writeLine(QString("%1 %2 started %3")
              .arg(qApp->applicationName())
              .arg(qApp->applicationVersion())
              .arg(locale.toString(QDateTime::currentDateTime())));
    CONNECT(this, &FaceConsole::processingStarted,
            this, &FaceConsole::nextFile);
    CONNECT(this, &FaceConsole::processed,
            this, &FaceConsole::nextFile);
    CONNECT(this, &FaceConsole::processingComplete,
            qApp, &QCoreApplication::quit);
    EMIT(applicationInitd());
    QTimer::singleShot(100, this, &FaceConsole::setupCommandLine);
}

void FaceConsole::enqueueNext()
{
    TRACEQFI << commandLine()->firstPositionalArgument();
    QString fileNameArgument = commandLine()->firstPositionalArgument();
}

void FaceConsole::setupCommandLine()
{
    TRACEFN
    rCommandLine().process();
    rCommandLine().expandDirectories();
    EMIT(commandLineSetup());
    QTimer::singleShot(100, this, &FaceConsole::setConfiguration);

}

void FaceConsole::setConfiguration()
{
    TRACEFN;
    cmpConfigObject->set(commandLine()->configuration());
    writeLine("---Configuration:");
    writeLines(commandLine()->configuration().dumpList());

    EMIT(configurationSet());
    QTimer::singleShot(100, this, &FaceConsole::setBaseOutputDir);
}

void FaceConsole::setBaseOutputDir()
{
    TRACEFN;

    QString baseDirString(config()->configuration("/Output").string("BaseDir"));
    baseDirString.replace("@", QDateTime::currentDateTime()
        .toString("DyyyyMMdd-Thhmm"));
    DUMPVAL(baseDirString);
    QDir baseDir(baseDirString);
    EXPECT(baseDir.mkpath("."));
    EXPECT(baseDir.cd("."));
    EXPECT(baseDir.exists());
    DUMPVAL(baseDir);
    DUMPVAL(baseDir.exists());
    if (baseDir.exists()) mBaseOutputDir = baseDir;
    EMIT(baseDirSet());
    QTimer::singleShot(100, this, &FaceConsole::setOutputDirs);
}

void FaceConsole::setOutputDirs()
{
    TRACEFN;

    bool created = false;
    mMarkedRectOutputDir.setNull(true);
    QString markedRectDirString(config()->
            configuration("Output/Dirs")
                .string("MarkedRect"));
    DUMPVAL(markedRectDirString);
#if 1
    if (markedRectDirString.isEmpty())
    {
        // do nothing, leave mMarkedRectOutputDir null
    }
    else if (QDir::isRelativePath(markedRectDirString))
    {
        QDir relativeDir(mBaseOutputDir);
        DUMPVAL(relativeDir);
        if ( ! relativeDir.exists(markedRectDirString))
            created = relativeDir.mkpath(markedRectDirString);
        EXPECT(relativeDir.cd(markedRectDirString));
        DUMPVAL(relativeDir);
        EXPECT(relativeDir.exists());
        DUMPVAL(relativeDir.exists());
        if (relativeDir.exists())
            mMarkedRectOutputDir = relativeDir;
        // else mMarkedRectOutputDir is still null
    }
    else if (QDir::isAbsolutePath(markedRectDirString))
    {
        QDir absoluteDir(markedRectDirString);
        if ( ! absoluteDir.exists())
            created = absoluteDir.mkpath(".");
        if (absoluteDir.exists())
            mMarkedRectOutputDir = absoluteDir;
        // else mMarkedRectOutputDir is still null
    }
    else
    {
        writeErr(QString("***%1 Dir = %2 is invalid").arg("MarkedRect").arg(markedRectDirString));
    }
#else
    QQFileInfo markedRectDirFileInfo(mBaseOutputDir, markedRectDirString);
    DUMPVAL(markedRectDirFileInfo);
    DUMPVAL(markedRectDirFileInfo.exists());
    if (markedRectDirFileInfo.exists())
    {
        EXPECTNOT(markedRectDirFileInfo.isFile());
        mMarkedRectOutputDir = QDir(markedRectDirFileInfo.path());
        writeLine("   " + mMarkedRectOutputDir.absolutePath() + " exists");
    }
    else
    {
        mMarkedRectOutputDir = markedRectDirFileInfo.dir();
        EXPECT(mMarkedRectOutputDir.mkpath(markedRectDirString));
        EXPECT(mMarkedRectOutputDir.cd(markedRectDirString));
        EXPECT(mMarkedRectOutputDir.exists());
        if (mMarkedRectOutputDir.exists())
            writeLine("   " + mMarkedRectOutputDir.absolutePath() + " created");
    }
#endif
    DUMPVAL(mMarkedRectOutputDir.isNull());
    DUMPVAL(mMarkedRectOutputDir);
    if (mMarkedRectOutputDir.notNull())
        writeLine("---"+mMarkedRectOutputDir.absolutePath()
                  + (created ? " created" : " exists"));

    NEEDDO(OtherDirs);
    TODO(BackToImageIO);
    EMIT(outputDirsSet());
    QTimer::singleShot(100, this, &FaceConsole::initializeResources);
}

void FaceConsole::initializeResources()
{
    TRACEFN;
    QDir baseCascadeDir(config()->configuration("/Resources/RectFinder")
                 .string("BaseDir"));
    QString cascadeFileName = config()->
            configuration("/Resources/RectFinder/PreScan")
                .string("XmlFile");
    QFileInfo cascadeFileInfo(baseCascadeDir, cascadeFileName);
    TRACE << cascadeFileInfo << cascadeFileInfo.exists()
          << cascadeFileInfo.isReadable() << cascadeFileInfo.isFile();
    EXPECT(cascadeFileInfo.exists());
    EXPECT(cascadeFileInfo.isReadable());
    EXPECT(cascadeFileInfo.isFile());
    write("---Cascade: "+cascadeFileInfo.absoluteFilePath()+" loading...");
    mPreScanCascade.loadCascade(cascadeFileInfo.absoluteFilePath());
    EXPECT(mPreScanCascade.isLoaded());

    NEEDDO(mPreScanCascade.configure);
    Configuration preScanConfig = config()->configuration("Option/RectFinder");
    preScanConfig += config()->configuration("PreScan/RectFinder");
    mPreScanCascade.configure(preScanConfig);

    writeLine("done");
    EMIT(resoursesInitd());
    QTimer::singleShot(100, this, &FaceConsole::startProcessing);}

void FaceConsole::startProcessing()
{
    TRACEFN;

    NEEDDO(more);
    EMIT(processingStarted());
}

void FaceConsole::nextFile()
{
    TRACEQFI << commandLine()->positionalArgumentSize();
    if (commandLine()->positionalArgumentSize() > 0)
    {
        mCurrentFileInfo = QFileInfo(rCommandLine().takePositionalArgument());
        DUMPVAL(mCurrentFileInfo);
        QTimer::singleShot(100, this, &FaceConsole::processCurrentFile);
    }
    else
    {
        QTimer::singleShot(100, this, &FaceConsole::finishProcessing);
    }
}

void FaceConsole::processCurrentFile()
{
    TRACEQFI << mCurrentFileInfo << mCurrentFileInfo.isReadable();
    QImage rectImage;
    QString markedRectOutputFileInfo;

    writeLine("---Processing: "+mCurrentFileInfo.absoluteFilePath());
    mPreScanCascade.imreadInputMat(mCurrentFileInfo);
    mCurrentRectangles = mPreScanCascade.detect();
    writeLine(QString("   %1 PreScan rectangles found")
                            .arg(mCurrentRectangles.size()));
    markedRectOutputFileInfo = QQFileInfo(mMarkedRectOutputDir,
                        mCurrentFileInfo.completeBaseName()+"-%M@.png")
                                  .absoluteFilePath();
    writeLine("   " + mPreScanCascade.imwriteMarkedImage(markedRectOutputFileInfo) + " written");
    EMIT(processed(QFileInfo(mCurrentFileInfo),
             mCurrentRectangles.size()));
    NEEDDO(processFailed());
    /*
    else
    {
        EMIT(processFailed(mCurrentFileInfo, "Error locating face objects"));
    }
    */
    NEEDDO(more);
}

void FaceConsole::finishProcessing()
{
    TRACEFN;
    writeLine("===Processing Complete");
    NEEDDO(more);
    EMIT(processingComplete());
}
