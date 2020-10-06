// file: {repo: EIRC2}./src/libs/eirExe/ApplicationHelper.h
#pragma once
#include "eirExe.h"

#include <QObject>

#include <QDateTime>
#include <QFile>
#include <QFlags>
#include <QTemporaryDir>

#include <eirType/Var.h>
#include <eirType/VersionInfo.h>
class ErrorHandler;

class CommandLine;
class CommandLineClientInterface;
class Settings;

class EIREXE_EXPORT ApplicationHelper : public QObject
{
    Q_OBJECT
public:
    enum Flag
    {
        NoFLag                  = 0,
        ExpandCommandLineDirs   = 0x00000001,
    };
    Q_DECLARE_FLAGS(Flags, Flag)

public:
    explicit ApplicationHelper(const Flags flags);
    void setFlags(const Flags flags);
    VersionInfo version() const;
    QStringList arguments() const;
    void set(CommandLineClientInterface const * client) const;
    void set(const VersionInfo & verInfo);

public slots:
    void run();

protected:

private slots:
    void initCommandLine();

signals:
    void commandLineInitd();

private:
    Flags mFlags=NoFLag;
    VersionInfo cmVerInfo;
};


