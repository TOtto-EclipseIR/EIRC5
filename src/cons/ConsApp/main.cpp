#include <QCoreApplication>

#include "../../../libs/eirBase/VersionInfo.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    VersionInfo::version().dump();
    return a.exec();
}
