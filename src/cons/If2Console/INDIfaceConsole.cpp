// file: {repo: EIRC2}./src/cons/INDIfaceConsole.cpp
#include "INDIfaceConsole.h"

#include <QDateTime>
#include <QFileInfo>
#include <QTimer>

#include <eirXfr/Debug.h>
#include <eirType/QQFileInfo.h>
#include <eirExe/CommandLine.h>
#include <eirExe/CommandLineClientInterface.h>
#include <eirExe/ConfigObject.h>
#include <eirExe/FileInfoQueue.h>
#include <eirExe/FileName.h>
//#include <eirExe/LegacySettings.h>
//#include <eirHaar/cvVersion.h>
//#include <eirImage/ImagePakWriterQueue.h>

#include "If2CommandLine.h"

INDIfaceConsole::INDIfaceConsole(Console *parent)
    : Console(parent)
    , mpConfig(new ConfigObject(parent))
{
    TRACEFN
    setObjectName("INDIfaceConsole");
    QTimer::singleShot(100, this, &INDIfaceConsole::initializeApplication);
    TRACERTV()
}

void INDIfaceConsole::initializeApplication()
{
    TRACEFN
    writeLine(">>>Hello INDI Console from initializeApplication() at "
                       + QDateTime::currentDateTime().toString());
    writeLine(QString("   %1 %2 from %3")
              .arg(core()->applicationName())
              .arg(core()->applicationVersion())
              .arg(core()->organizationName()));
    writeLine("===Raw Executable Arguments:");
    foreach (QString arg, CMD->exeArguments())
        writeLine("---{" + arg + "}");
//    cvVersion opencvVersion;
  //  writeLine("==="+opencvVersion.toString());
    EMIT(applicationInitd());
    QTimer::singleShot(100, this, &INDIfaceConsole::setupCommandLine);
}


void INDIfaceConsole::setupCommandLine()
{
    TRACEFN
    If2CommandLine interface;
    CMD->().set(&interface);
    CMD->().process();
    CMD->().set(nullptr);
    CMD->().expandDirectories();
    EMIT(commandLineSetup());
    QTimer::singleShot(100, this, &INDIfaceConsole::setConfiguration);
}

void INDIfaceConsole::setConfiguration()
{
    TRACEQFI << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>INDIfaceConsole::setConfiguration()";
    mpConfig->set(CMD->configuration());

    config()->configuration("Output").dump();
    config()->configuration("/Output").dump();
    QString baseDirString(config()->configuration("/Output").string("BaseDir"));
    QString rectDirString(config()->configuration("/PreScan/Face/Output").string("RectDir"));

    baseDirString.replace("@", QDateTime::currentDateTime()
        .toString("DyyyyMMdd-Thhmm"));
    rectDirString.replace("@", QDateTime::currentDateTime()
        .toString("DyyyyMMdd-Thhmm"));
    mRectDir = QDir(baseDirString);
    mRectDir.mkpath(rectDirString);
    mRectDir.cd(rectDirString);
TRACE << baseDirString << rectDirString
      << mRectDir.absolutePath();

    QTimer::singleShot(100, this, &INDIfaceConsole::initializeResources);
}

void INDIfaceConsole::initializeResources()
{
    TRACEQFI << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>INDIfaceConsole::initializeResources()";

    QFileInfo faceCascadeFileInfo(
                QDir(mpConfig->configuration("/Resources/ObjDet").string("BaseDir")),
                mpConfig->configuration("/PreScan/Resources/ObjDet/Face").string("XmlFile"));
    TRACE << faceCascadeFileInfo.absoluteFilePath()
          << faceCascadeFileInfo.exists()
          << faceCascadeFileInfo.isReadable();

    bool loaded = mFaceFinder.loadCascade(faceCascadeFileInfo);
    DUMPVAL(loaded);
    mFaceParms.configure(
                mFaceFinder.coreSize(),
                mpConfig->configuration("/PreScan/Face/ObjDet"));
    NEEDDO(mFaceFinder.config());

    EMIT(resoursesInitd());
    QTimer::singleShot(100, this, &INDIfaceConsole::startProcessing);
}

void INDIfaceConsole::startProcessing()
{
    TRACEFN
    mImageFileQueue = CMD->positionalArgumentList();
    TRACE << mImageFileQueue;
    TODO(?)
    QTimer::singleShot(100, this, &INDIfaceConsole::nextFile);
}

void INDIfaceConsole::nextFile()
{
    TRACEQFI << "mImageFileQueue.size()" << mImageFileQueue.size();
    while ( ! mImageFileQueue.isEmpty())                    /* /-----\ */
    {
        QString filePathName = mImageFileQueue.takeFirst();
        TRACEQFI << filePathName << "taken" << mImageFileQueue.size();
        if (filePathName.isEmpty())  continue;              /* \-----/ */
        mCurrentImageFileName = filePathName;
        QTimer::singleShot(100, this, &INDIfaceConsole::processFile);
        return;                                             /* /=====\ */
    }
    QTimer::singleShot(100, this, &INDIfaceConsole::finishProcessing);
}                                                           /* \=====/ */

void INDIfaceConsole::processFile()
{
    TRACEQFI << "mCurrentImageFile:" << mCurrentImageFileName;
    processImage();
    TODO(more?)
    QTimer::singleShot(100, this, &INDIfaceConsole::nextFile);
}

void INDIfaceConsole::finishProcessing()
{
    TRACEFN
    NEEDDO(it)
    QTimer::singleShot(100, core(), &QCoreApplication::quit);
}

void INDIfaceConsole::processImage()
{
    TRACEQFI << mCurrentImageFileName;

    writeLine(QString("===Processing: %1").arg(mCurrentImageFileName));
    mFaceFinder.loadImage(mCurrentImageFileName);
    DUMPVAL(mFaceFinder.cascadeLoaded());
    BEXPECT(mFaceFinder.cascadeLoaded());
//    DUMPVAL(mFaceFinder.imageLoaded());
  //  BEXPECT(mFaceFinder.imageLoaded());
//    BEXPECT(mFaceFinder.detectMat().save("/Detect.PNG"));

    int faceCount = mFaceFinder.find(mFaceParms);
    writeLine("   " + QString::number(faceCount)
              + " Face Rectangles Detected");
    QFileInfo inputFI(mCurrentImageFileName);
    QFileInfo rectFI(mRectDir,
                     inputFI.completeBaseName()+".PNG");
    bool rectImageSaved = mFaceFinder.rectImage()
            .save(rectFI.filePath(), "PNG");
    EXPECT(rectImageSaved);
    EXPECT(rectFI.exists());
    if (rectImageSaved && rectFI.exists())
        writeLine("    " + rectFI.absoluteFilePath() + " saved");
    NEEDDO(more);
    TRACERTV()
}
