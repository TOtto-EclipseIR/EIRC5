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

#include <eirBase/UInt128.h>

int main(int argc, char *argv[])
{
    UInt128 u128;
    UInt128 u2(1,0x0123456789ABCDEF);

    QCoreApplication a(argc, argv);
    a.setApplicationName("INDI5faceConsole");
    a.setApplicationVersion(VER_STRING " " VER_TRUNKNAME);
    a.setOrganizationName(VER_ORGNAME);
    sdo->start(argv[0], "./log");

    FaceConsole c(a.parent()); Q_UNUSED(c);
    return a.exec();
}
