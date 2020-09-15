// file: {EIRC2 Repo}./src/libs/eirExe/CommandLine.h
#pragma once
#include "eirExe.h"

#include <QObject>

#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QFileInfoList>
#include <QStateMachine>
class QCommandLineParser;

#include <eirType/MultiName.h>
#include <eirType/Var.h>
#include <eirType/VarMap.h>
#include <eirType/Sortable.h>
#include <eirType/QQFileInfo.h>
#include <eirType/QQFileInfoList.h>

#include "Configuration.h"
class CommandLineClientInterface;
class LegacySettings;

#include "../../version.h"

class EIREXE_EXPORT CommandLine : public QObject
{
    Q_OBJECT
public:
    explicit CommandLine(QObject *parent = nullptr);
    void set(CommandLineClientInterface * interface);
    int positionalArgumentSize() const;
    QStringList positionalArgumentList() const;
    QString firstPositionalArgument() const;
    QString takePositionalArgument();
    const QStringList exeArguments(bool withNumbers=false) const;
    const QQFileInfo exeFileInfo() const;
    Configuration configuration() const;

public slots:
    void process();
    void expandDirectories(const int recurseDepth=-1);
    void dump();

signals:
    void constructed(void);

protected:
    // processing
    QStringList expandFileArguments(const QStringList qsl,
                                    const QChar trigger=QChar('@'));
    QStringList extractDirectiveArguments(const QStringList &currentArgs);
    QStringList parseQtOptions(const QStringList &currentArgs);
    QStringList stripConfiguration(const QStringList &expandedArgs,
                                   const MultiName &prefix=MultiName(),
                                   const QChar &trigger=QChar('/'));
    // utility
    void parseConfigArgument(const QString &arg,
                             const MultiName &prefix=MultiName());
    QStringList readTxtFileArguments(const QFileInfo &argFileInfo);

private slots:
    void dumpPositionalArgs() const;

private:
    const QStringList cmExeArgumentList;
    QFileInfo mExeFileInfo;
    CommandLineClientInterface * mpInterface=nullptr;
    LegacySettings * mpLegacySettings=nullptr;
    QStringList mPositionalArgumentList;
    Configuration mConfiguration;
};
