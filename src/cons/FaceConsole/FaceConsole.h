#pragma once

#include <QObject>
#include <eirExe/Console.h>

class QCommandLineParser;

#include <eirType/QQDir.h>
#include <eirObjDet/ObjectDetection.h>
#include <eirObjDet/ObjDetResultList.h>
#include <eirQtCV/cvVersion.h>

class FaceConsole : public Console
{
    Q_OBJECT
public:
    explicit FaceConsole();

public slots:
    void initializeApplication();

private slots:
    void processCommandLine();
    void setConfiguration();
    void initializeResources();
    void setBaseOutputDir();
    void setOutputDirs();
    void startProcessing();
    void nextFile();
    void processCurrentFile();
    void finishProcessing();
    void failedExit(const qint8 retcode, const QString &errmsg);
    void catchSettingsGet(const Settings::Key key, const Settings::Value valu);
    void catchSettingsImport(const Settings::Key key, const Settings::Value valu);
    void catchSettingsCreate(const Settings::Key key, const Settings::Value valu);
    void catchSettingsDefault(const Settings::Key key, const Settings::Value valu);
    void catchSettingsRemove(const Settings::Key key, const Settings::Value valu);
    void catchSettingsChange(const Settings::Key key, const Settings::Value newValu, const Settings::Value oldValu);
    void catchSettingsGroup(const Settings::Key key);
    void catchCommandLineWarning(const QString what, const QString why);
    void catchCommandLineInfo(const QString what, const QString why);


signals:
    void applicationInitd();
    void commandLineProcessed();
    void configurationSet();
    void baseDirSet();
    void outputDirsSet();
    void resoursesInitd();
    void resourseInitFailed(const qint8 retcode, const QString &errmsg);
    void processingStarted();
    void processed(const QFileInfo &fileInfo, const int rectCount);
    void processFailed(const QFileInfo &fileInfo, const QString &errorString);
    void processEmpty(const QFileInfo &fileInfo, const QString &methodString);
    void processingComplete();

private:
    bool mWriteInfo=true;
    //QQString mMethodString;
    QDir mBaseOutputDir;
    QQDir mMarkedRectOutputDir;
    //QQDir::Vector mMarkedFaceQualityDirs;
    int mCurrentFileCount=0;
    QQFileInfo mCurrentFileInfo;
    QQRectList mCurrentRectangles;
    ObjDetResultList mCurrentResults;
    QImage mRectImage;
};

