// file: {EIRC2 repo}./src/cons/If2Console/main.cpp

#include <QCoreApplication>
#include "INDIfaceConsole.h"

#include "../../version.h"

#include <QTimer>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    a.setApplicationName("If2Console");
    a.setApplicationVersion(EIRC2_VER_STRING " " EIRC2_VER_TRUNKNAME);
    a.setOrganizationName(EIRC2_VER_ORGNAME);
    INDIfaceConsole * c = new INDIfaceConsole();
    Q_UNUSED(c);
    return a.exec();
}
