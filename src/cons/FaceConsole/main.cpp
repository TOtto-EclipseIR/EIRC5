#include <QCoreApplication>

#include"FaceConsole.h"

#include "../../version.h"

#include <QtGlobal>
#include <QtDebug>
#include <QByteArray>
#include <QDateTime>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QTimer>

#include <eirXfr/StartupDebug.h>
Q_GLOBAL_STATIC(StartupDebug, sdo)

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    a.setApplicationName("INDI5faceConsole");
    a.setApplicationVersion(VER_STRING " " VER_TRUNKNAME);
    a.setOrganizationName(VER_ORGNAME);
    sdo->start(argv[0], "./log");

    FaceConsole c; Q_UNUSED(c);
    return a.exec();
}
