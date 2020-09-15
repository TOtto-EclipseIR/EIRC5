// file: {EIRC2 Repo}./src/libs/eirExe/CommandLine.h
#pragma once
#include "eirExe.h"

#include <QObject>

#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QDir>
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
    struct ExpandDirResult
    {
        QDir dir;
        QString firstFileName;
        int fileCount;
    };
    typedef QList<ExpandDirResult> ExpandDirResultList;

public:
    explicit CommandLine(QObject *parent = nullptr);
    void set(CommandLineClientInterface * interface);
    ExpandDirResultList expandDirResults() const;
    int positionalArgumentSize() const;
    QStringList positionalArgumentList() const;
    QString firstPositionalArgument() const;
    QString takePositionalArgument();
    int takePositionalArgumentCount() const;
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
    QQFileInfo mExeFileInfo;
    CommandLineClientInterface * mpInterface=nullptr;
    LegacySettings * mpLegacySettings=nullptr;
    ExpandDirResultList mExpandDirResultList;
    QStringList mPositionalArgumentList;
    int mPositionalArgumentsTaken=0;
    Configuration mConfiguration;
};
