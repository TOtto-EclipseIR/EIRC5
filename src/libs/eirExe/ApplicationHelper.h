// file: {repo: EIRC2}./src/libs/eirExe/ApplicationHelper.h
#pragma once
#include "eirExe.h"

#include <QObject>

#include <QDateTime>
#include <QFile>
#include <QTemporaryDir>

#include <eirType/Var.h>
#include <eirType/VersionInfo.h>
class ErrorHandler;

class CommandLine;
class CommandLineClientInterface;
class SettingsFile;

class EIREXE_EXPORT ApplicationHelper : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationHelper(QObject *parent = nullptr);
    VersionInfo version() const;
    void set(CommandLineClientInterface const * client) const;
    void set(const VersionInfo & verInfo);
    QFile * tempDirFile(const QString &ext,
                     QObject * parent=nullptr);
    const CommandLine *commandLine() const;
    CommandLine &rCommandLine(); // non-const
    SettingsFile *settings() const;

public slots:
    void run();

protected:

private slots:
    void initCommandLine();

signals:
    void commandLineInitd();

private:
    VersionInfo cmVerInfo;
    QTemporaryDir const * cmpTempDir=nullptr;
    CommandLine * const cmpCommandLine=nullptr;
    SettingsFile * const cmpSettings=nullptr;
};

