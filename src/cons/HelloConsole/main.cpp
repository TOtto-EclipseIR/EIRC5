#include <QCoreApplication>
#include "HelloConsole.h"

#include <cstdlib>
#include <iostream>

//#include <eirXfr/StartupDebug.h>
//Q_GLOBAL_STATIC(StartupDebug, sdo)

#include"HelloConsole.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    sdo->start(argv[0], "./log");
    // from here on, all QtDebug messages should be sent to start log file
    // until sdo->finish() is called, typically in XFR::start().

    a.setApplicationName("HelloConsole");

    HelloConsole c(a.parent());
    Q_UNUSED(c);

    return a.exec();
}
