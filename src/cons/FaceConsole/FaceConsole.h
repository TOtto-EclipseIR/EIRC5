#pragma once

#include <QObject>
#include <eirExe/Console.h>

#include <eirType/QQDir.h>
#include <eirObjDet/ObjDetProcessor.h>
#include <eirObjDet/ObjDetResultList.h>

class QCommandLineParser;

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
    void processed(QFileInfo fileInfo, int rectCount);
    void processFailed(QFileInfo fileInfo, QString errorString);
    void processingComplete();

private:
    /*
    ObjDetProcessor mPreScanProcessor;
    unsigned mScaleFactor=120;
    signed mNeighbors=1;
    unsigned mMinQuality=0;
    */
    QQString mMethodString;
    QDir mBaseOutputDir;
    QQDir mMarkedRectOutputDir;
    //QQDir::Vector mMarkedFaceQualityDirs;
    int mCurrentFileCount=0;
    QQFileInfo mCurrentFileInfo;
    QQRectList mCurrentRectangles;
    ObjDetResultList mCurrentResults;
    QImage mRectImage;
};

