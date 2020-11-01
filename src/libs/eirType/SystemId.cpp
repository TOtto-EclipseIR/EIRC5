#include "SystemId.h"

#include <QHostInfo>
#include <QNetworkInterface>
#include <QTimeZone>

#include "Milliseconds.h"


SystemId::SystemId(const Flags f, const MultiName &name)
    : VarMap(name)
{
    if (f & SystemInfo)     addSystemInfo();
    if (f & NetworkInfo)    addNetworkInfo();
}

void SystemId::addSystemInfo()
{
    VarMap::insert("SysInfo/TimeStamp", Milliseconds::baseString());
    VarMap::insert("SysInfo/TimeZoneId", QTimeZone::systemTimeZoneId());
    VarMap::insert("SysInfo/Machine/UniqueId", QSysInfo::machineUniqueId());
    VarMap::insert("SysInfo/Machine/HostName", QSysInfo::machineHostName());
    VarMap::insert("SysInfo/Kernel/TypeName", QSysInfo::kernelType());
    VarMap::insert("SysInfo/Kernel/Version", QSysInfo::kernelVersion());


}

void SystemId::addNetworkInfo()
{
    QNetworkInterface qni = QNetworkInterface::interfaceFromIndex(0);
    if (qni.isValid())
        VarMap::insert("SysInfo/Network/HardwareID", qni.hardwareAddress());
    VarMap::insert("SysInfo/Network/LocalHostName", QHostInfo::localHostName());

}
