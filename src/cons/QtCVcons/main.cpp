#include <QCoreApplication>
#include "QtcvConsole.h"

#include <eirQtCV/cvCascade.h>
//#include <eirXfr/StartupDebug.h>
//Q_GLOBAL_STATIC(StartupDebug, sdo)

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //sdo->start(argv[0], "./log");
    QtcvConsole c(ApplicationHelper::ExpandCommandLineDirs); Q_UNUSED(c);
    return a.exec();
}
