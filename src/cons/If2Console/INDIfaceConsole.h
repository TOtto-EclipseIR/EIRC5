// file: {eirC2 repo}./src/apps/cons/If2Console/INDIfaceConsole.h
#pragma once

#include <QObject>
#include <eirExe/Console.h>

#include <QDir>
#include <QFileInfo>
#include <QImage>
#include <QList>

#include <eirType/VarPak.h>
#include <eirType/QQFileInfo.h>
#include <eirType/QQFileInfoList.h>
#include <eirType/QQRectList.h>
#include <eirType/Region.h>
#include <eirExe/ApplicationHelper.h>
#include <eirExe/XmlFile.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>

#include "cvMat.h"
#include "RectCascade.h"
#include "RectFinder.h"
#include "RectFinderParameters.h"

class ColorImage;
class CommandLine;
class FileInfoQueue;
class ImagePakWriterQueue;

#include "../../version.h"

class INDIfaceConsole : public Console
{
    Q_OBJECT
public:
    explicit INDIfaceConsole(Console *parent = nullptr);

public slots:
    void initializeApplication();

private slots:
    void setupCommandLine();
    void setConfiguration();
    void initializeResources();
    void startProcessing();
    void nextFile();
    void processFile();
    void finishProcessing();

signals:
    void applicationInitd();
    void commandLineSetup();
    void configurationSet();
    void resoursesInitd();
    void processingStarted();
    void processingImage(QFileInfo qfi);
    void imageWritten(const QFileInfo qfi, QImage image);
    void imageProcessed(QFileInfo qfi);
    void processingComplete();

protected:
    void processImage();

private:
    CommandLineClientInterface * mpCommandLineInterface=nullptr;
    ConfigObject * mpConfig=nullptr;
    QStringList mImageFileQueue;
//    RectCascade mFaceCascade;
    RectFinder mFaceFinder;
    RectFinderParameters mFaceParms;
    QString mCurrentImageFileName;
    QDir mRectDir;
    cvMat mInputMat;
};
