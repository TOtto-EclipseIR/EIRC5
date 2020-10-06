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
#include <eirType/QQString.h>
#include <eirType/QQStringList.h>
#include <eirType/QQStringStdList.h>

#include "ApplicationHelper.h"
class CommandLineClientInterface;

#include "Settings.h"

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
    QQStringList positionalArgumentList() const;
    QQString firstPositionalArgument() const;
    QQString takePositionalArgument();
    int positionalArgumentsTaken() const;
    const QQStringList exeArguments(bool withNumbers=false) const;
    const QQFileInfo exeFileInfo() const;

public slots:
    void process(const ApplicationHelper::Flags flags);
    void dump();
    void dumpPositionalArgs() const;

signals:
    void constructed(void);
    void info(const QString what, const QString why);
    void warning(const QString what, const QString why);

protected slots:
    void extractDirectiveArguments();
    void stripSettings(const Settings::Key &prefix=Settings::Key(), const QChar &trigger=QChar('/'));
    void expandDirectories(const int recurseDepth=-1);

protected:
    void expandFileArguments(const QChar trigger=QChar('@'));
    void parseQtOptions();
    void parseSettingArgument(const QString &arg, const Settings::Key &prefix=Settings::Key());
    QQStringList readTxtFileArguments(const QQFileInfo &argFileInfo);

private slots:

private:
    const QQStringList cmExeArgumentList;
    QQFileInfo mExeFileInfo;
    QQStringList mRemainingArgumentList;
    CommandLineClientInterface * mpInterface=nullptr;
    ExpandDirResultList mExpandDirResultList;
    QQStringList mPositionalArgumentList;
    int mPositionalArgumentsTaken=0;
};
