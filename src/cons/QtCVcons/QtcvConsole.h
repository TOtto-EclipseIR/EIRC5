#pragma once

#include <eirExe/Console.h>
#include <QObject>

class QtcvConsole : public Console
{
    Q_OBJECT
public:
    QtcvConsole(const Flags flags);

private slots:
    void initialize();
    void start();

signals:
    void ctord();
    void initialized();

};

