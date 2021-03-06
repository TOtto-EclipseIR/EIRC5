#include "StartupDebug.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QDir>
#include <QIODevice>

#include <cstdlib>
#include <iostream>

QTextStream * StartupDebug::smpTextStream=nullptr;

StartupDebug::StartupDebug() {;}

bool StartupDebug::start(const QString &exeArg0,
                         const QString &logDirName)
{
    //std::cout << "Starting Startup Debugging Output handler\n"; flush(std::cout);
    QFileInfo exeFileInfo = QFileInfo(exeArg0);
    QFile * mpStartupFile = new QFile(qApp->parent());
    Q_ASSERT(mpStartupFile);
    QString startupFileName = QString("%1-StartLog-%2.txt")
            .arg(exeFileInfo.completeBaseName())
            .arg(QDateTime::currentDateTime().toString("DyyyyMMdd-Thhmm"));
    QDir startupDir = QDir::current();
    startupDir.mkpath(logDirName);
    startupDir.cd(logDirName);
    QFileInfo startupFileInfo(startupDir, startupFileName);

    mpStartupFile->setFileName(startupFileInfo.filePath());
    if ( ! mpStartupFile->open(QIODevice::WriteOnly
                         | QIODevice::Text
                         | QIODevice::Truncate))
         std::cerr << mpStartupFile->errorString().toLocal8Bit().constData() << Qt::endl;
    flush(std::cerr);
    if (mpStartupFile->isWritable())
    {
        //std::cout << "Startup Debugging Output enabled\n"; flush(std::cout);
        smpTextStream = new QTextStream(mpStartupFile);
        qInstallMessageHandler(myStartupMessageHandler);
    }  // else stay with stderr
    return nullptr != smpTextStream;
}

void StartupDebug::finish()
{
    qInstallMessageHandler(0);
    delete smpTextStream;
    smpTextStream = nullptr;
    mpStartupFile->close();
}

void StartupDebug::myStartupMessageHandler(QtMsgType type,
               const QMessageLogContext &context,
               const QString &msg)
{
    Q_ASSERT_X(nullptr != smpTextStream,
               "StartupDebug::myStartupMessageHandler",
               "static QTextStream * smpTextStream");
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function
                         ? context.function : "";
    Q_UNUSED(localMsg); Q_UNUSED(file); Q_UNUSED(function);

    switch (type)
    {
    case QtDebugMsg:
    case QtInfoMsg:
    case QtWarningMsg:
    case QtCriticalMsg:
    case QtFatalMsg:
        *smpTextStream << msg << Qt::endl;
        smpTextStream->flush();
        break;
    }
}
