#include "FaceConsole.h"

#include <QDateTime>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QTimer>

#include <eirExe/CommandLine.h>
#include <eirExe/SettingsFile.h>
#include <eirImage/HeatmapMarker.h>
#include <eirImage/SimpleRectMarker.h>
#include <eirObjDet/ObjectDetector.h>
#include <eirQtCV/cvVersion.h>
#include <eirType/Success.h>
#include <eirXfr/Debug.h>
#include <eirXfr/StartupDebug.h>

FaceConsole::FaceConsole(QObject *parent)
    : Console(parent)
{
    TRACEFN;
    setObjectName("FaceConsole");
    QTimer::singleShot(500, this, &FaceConsole::initializeApplication);
    TRACERTV();
}

SettingsFile *FaceConsole::settings() const
{
    return commandLine()->settings();
}

void FaceConsole::initializeApplication()
{
    TRACEFN;
    QLocale locale;
    cvVersion cvv;
    TODO(WhyZero);
    writeLine(QString("%1 %2 started %3")
              .arg(qApp->applicationName())
              .arg(qApp->applicationVersion())
              .arg(locale.toString(QDateTime::currentDateTime())));
    writeLine("   with Open Source Computer Vision library (OpenCV) " + cvv.getString());
    CONNECT(this, &FaceConsole::resourseInitFailed,
            qApp, &QCoreApplication::quit);
    CONNECT(this, &FaceConsole::processingStarted,
            this, &FaceConsole::nextFile);
    CONNECT(this, &FaceConsole::processed,
            this, &FaceConsole::nextFile);
    CONNECT(this, &FaceConsole::processingComplete,
            qApp, &QCoreApplication::quit);
    CONNECT(this, &FaceConsole::resourseInitFailed,
            this, &FaceConsole::failedExit);
    TSTALLOC(settings());
    TRACE << QOBJNAME(settings());
    new ObjectDetector(cvCascade::PreScan, this);
    TSTALLOC(ObjectDetector::p(cvCascade::PreScan));
    SettingsFile::Map objDetMap = settings()->extract("ObjectDetector");
    objDetMap.dump();
    ObjectDetector::p(cvCascade::PreScan)->initialize(objDetMap);
    EMIT(applicationInitd());
    QTimer::singleShot(100, this, &FaceConsole::processCommandLine);
}

void FaceConsole::enqueueNext()
{
    TRACEQFI << commandLine()->firstPositionalArgument();
    QString fileNameArgument = commandLine()->firstPositionalArgument();
}

void FaceConsole::processCommandLine()
{
    TRACEFN;
    rCommandLine().process();
    rCommandLine().expandDirectories();
    CommandLine::ExpandDirResultList xdrl = commandLine()->expandDirResults();
    writeLine("---Directories:");
    int k = 0;
    foreach (CommandLine::ExpandDirResult xdr, xdrl)
        writeLine(QString("   %1. %2 %3 %4").arg(++k, 2).arg(xdr.fileCount, 4)
                  .arg(xdr.firstFileName, 20).arg(xdr.dir.path()));
    EMIT(commandLineProcessed());
    QTimer::singleShot(100, this, &FaceConsole::setConfiguration);
}

void FaceConsole::setConfiguration()
{
    TRACEFN;
    writeLine("---Configuration:");
    writeLines(commandLine()->settings()->map().toStringList());
    EMIT(configurationSet());
    QTimer::singleShot(100, this, &FaceConsole::setBaseOutputDir);
}

void FaceConsole::setBaseOutputDir()
{
    TRACEFN;
    QString baseDirString(settings()->map().string("/Output/BaseDir"));
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
    QString markedRectDirString(settings()->map().string("Output/Dirs/MarkedRect"));
    DUMPVAL(markedRectDirString);
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
        writeErr(QString("***%1 Dir = %2 is invalid").arg("MarkedRect")
                        .arg(markedRectDirString));
    }
    DUMPVAL(mMarkedRectOutputDir.isNull());
    DUMPVAL(mMarkedRectOutputDir);
    if (mMarkedRectOutputDir.notNull())
    {
        writeLine("---"+mMarkedRectOutputDir.absolutePath()
                  + (created ? " created" : " exists"));
        for (int q00 = 0; q00 < 10; ++q00)
        {
            QDir q00Dir = mMarkedRectOutputDir;
            QString q00Name = QString("Q%1").arg(q00 * 100, 3, 10, QChar('0'));
            q00Dir.mkpath(q00Name);
            if (q00Dir.cd(q00Name))
            {
                mMarkedFaceQualityDirs.append(q00Dir);
                writeLine("   "+q00Dir.absolutePath()+" created");
            }
        }
    }

    NEEDDO(OtherDirs);
    TODO(BackToImageIO);
    EMIT(outputDirsSet());
    QTimer::singleShot(100, this, &FaceConsole::initializeResources);
}

void FaceConsole::initializeResources()
{
    TRACEFN;
    QQDir baseCascadeDir(settings()->map().string("/Resources/RectFinder/BaseDir"));
    TRACE << baseCascadeDir << baseCascadeDir.exists() << baseCascadeDir.isReadable();
    EXPECT(baseCascadeDir.exists());
    EXPECT(baseCascadeDir.isReadable());
    QString cascadeFileName = settings()->map().
            string("/Resources/RectFinder/PreScan/XmlFile");
    QQFileInfo cascadeFileInfo(baseCascadeDir, cascadeFileName);
    TRACE << cascadeFileInfo.absoluteFilePath() << cascadeFileInfo.exists()
          << cascadeFileInfo.isReadable() << cascadeFileInfo.isFile();
    EXPECTNOT(cascadeFileInfo.notExists());
    EXPECTNOT(cascadeFileInfo.notReadable());
    EXPECTNOT(cascadeFileInfo.notFile());
    write("---Cascade: "+cascadeFileInfo.absoluteFilePath()+" loading...");
    if (cascadeFileInfo.notExists()
            || cascadeFileInfo.notFile()
            || cascadeFileInfo.notReadable())
    {
        writeLine("error");
        writeErr("***Invalid cascade file specified: "
                 + cascadeFileInfo.absoluteFilePath());
        EMIT(resourseInitFailed(1, "Invalid Cascade"));
    }

    EXPECT(ObjectDetector::p(cvCascade::PreScan)->load(cascadeFileInfo));
    if (ObjectDetector::p(cvCascade::PreScan)->isLoaded())
    {
        writeLine("done");
        EMIT(resoursesInitd());
        QTimer::singleShot(100, this, &FaceConsole::startProcessing);
    }
    else
    {
        writeLine("error");
        writeErr("***Cascade file load failed: "
                 + cascadeFileInfo.absoluteFilePath());
        EMIT(resourseInitFailed(2, "Cascade Load Failed"));
    }

    NEEDDO(cmpPreScanDetector->cascade()->configure);
//    Configuration preScanConfig = config()->configuration("Option/RectFinder");
  //  preScanConfig += config()->configuration("PreScan/RectFinder");
    //cmpPreScanDetector->cascade()->configure(preScanConfig);
}

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
    QString markedRectOutputFileName;

    writeLine(QString("---Processing: %1. %2").arg(++mCurrentFileCount)
              .arg(mCurrentFileInfo.fileName(QQString::Squeeze)));
    QQImage inputImage(mCurrentFileInfo.absoluteFilePath());
    if (inputImage.isNull())
    {
        writeLine("***Invalid Image File");
        EMIT(processed(QFileInfo(mCurrentFileInfo),0));
    }
    SettingsFile::Map preScanSettings = settings()->extract("Option/RectFinder");
    preScanSettings += settings()->extract("PreScan/RectFinder");
#if 1
    //QbjectDetector::p(cvCascade::PreScan)->process();
#else
    int rectCount = cmpPreScanDetector->cascade()->detectRectangles(preScanConfig, inputImage);
    DUMPVAL(rectCount);
    mCurrentRectangles = cmpPreScanDetector->cascade()->rectList();
    BEXPECTNOT(rectCount < 0);
    WEXPECTNOT(0 == rectCount);
    EXPECTEQ(rectCount, mCurrentRectangles.size());
    qreal unionGroupOverlap = cmpConfigObject->configuration("/PreScan/RectFinder")
            .realPermille("UnionGroupOverlap", 500);
    qreal unionGroupOrphan = cmpConfigObject->configuration("/PreScan/RectFinder")
            .unsignedInt("UnionGroupOrphan", 1);
    mCurrentResults = cmpPreScanDetector->groupByUnion(mCurrentRectangles,
                                                       unionGroupOverlap,
                                                       unionGroupOrphan);
    writeLine(QString("   %1 PreScan rectangles found, %2 Candidate Faces, %3 Orphans")
              .arg(rectCount).arg(mCurrentResults.count())
              .arg(mCurrentResults.orphanCount()));
    QQFileInfo markedRectOutputFileInfo(mMarkedRectOutputDir,
            mCurrentFileInfo.completeBaseName()+"-%M@.png", QQString::Squeeze);
    markedRectOutputFileInfo.replace("@", Milliseconds::baseDateStamp());
    markedRectOutputFileInfo.replace("%M", cmpPreScanDetector->cascade()->methodString());
    markedRectOutputFileName = markedRectOutputFileInfo.absoluteFilePath();
    //SimpleRectMarker rectMarker(inputImage);
    SimpleRectMarker rectMarker(cmpPreScanDetector->cascade()->detectImage());
    rectMarker.mark(Configuration(), mCurrentResults, rectMarker.qualityWheel(), true);
    QQImage markedImage = rectMarker;
    if (markedImage.save(markedRectOutputFileName))
        writeLine(QString("   %1 written").arg(markedRectOutputFileName));
    HeatmapMarker heatMarker(inputImage);
    heatMarker.mark(Configuration(), mCurrentResults);
    QQImage heatImage = heatMarker;
    QQFileInfo heatRectOutputFileInfo(mMarkedRectOutputDir,
            mCurrentFileInfo.completeBaseName()+"-heat.png", QQString::Squeeze);
    if (heatImage.save(heatRectOutputFileInfo.absoluteFilePath(QQString::Squeeze)))
        writeLine("   " + heatRectOutputFileInfo.absoluteFilePath() + " written");

    foreach (ObjDetResultItem item, mCurrentResults.list())
    {
        QQImage faceImage = markedImage.copy(item.resultRect() * 1.25);
        QString faceName = QString("%1-R%2Q%3.PNG")
                .arg(mCurrentFileInfo.completeBaseName(QQString::Squeeze))
                .arg(item.rank(), 2, 10, QChar('0'))
                .arg(item.quality(), 3, 10, QChar('0'));
        QQFileInfo faceInfo(mMarkedFaceQualityDirs.at(item.quality() / 100), faceName);
        if (faceImage.width() < 256)
            faceImage = faceImage.scaledToWidth(256, Qt::SmoothTransformation);
        bool saved = faceImage.save(faceInfo.absoluteFilePath());
        TRACE << saved << faceInfo << faceImage;
        if (saved)
            writeLine(QString("   %1 written").arg(faceInfo.filePath()));
    }
#endif

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

void FaceConsole::failedExit(const qint8 retcode, const QString &errmsg)
{
    TRACEQFI << retcode << errmsg;
    writeErr(QString("@@@Failure Code=%1: %2").arg(retcode).arg(errmsg));
    qApp->exit(retcode);
}
