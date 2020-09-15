#pragma once

#include <QObject>
#include <eirExe/Console.h>

class HelloConsole : public Console
{
    Q_OBJECT
public:
    HelloConsole(QObject * parent=nullptr);

public slots:
    void start();
    void tellSystem();
    void finish();

signals:
    void constructed();
    void started();
    void systemTold();
    void finished();
};

