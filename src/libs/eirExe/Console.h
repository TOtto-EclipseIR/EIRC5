#pragma once
#include "eirExe.h"

#include <QObject>
#include "ApplicationHelper.h"

#include <QCoreApplication>

class QFile;

class BaseCommandLine;


class EIREXE_EXPORT Console : public ApplicationHelper
{
    Q_OBJECT
    Q_PROPERTY(bool mForkQtDebug READ isForkQtDebug
        WRITE setForkQtDebug RESET resetForkQtDebug USER true)

public:
    explicit Console(QObject *parent = nullptr);
    /* The mechanism below is broken; simply use qApp-> for now
    QCoreApplication * core();
    QObject * appParent();
    */

    bool isForkQtDebug() const;

public slots:
    void putChar(const char c);
    void getChar();
    void readLine();
    void write(const QString &qs, const bool andFlush=true);
    void writeLine(const QString &qs, const bool andFlush=true);
    void writeLines(const QStringList &qsl);
    void writeErr(const QString &qs,
                  const bool andFlush=true);
    void writeErrs(const QStringList &qsl);

    void setForkQtDebug(bool mForkQtDebug);
    void resetForkQtDebug();

signals:
    void charPut(const char c);
    void charNotPut(const char c);
    void charGot(const char c);
    void charNotGot();
    void lineRead(const QByteArray line);
    void lineNotRead();

private:
    QCoreApplication * const cmpCoreApp=nullptr;

    QFile * mpIn=nullptr;
    QFile * mpOut=nullptr;
    QFile * mpErr=nullptr;
    bool m_ForkQtDebug=true;
};

