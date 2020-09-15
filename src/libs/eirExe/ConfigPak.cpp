#include "ConfigPak.h"

#include <eirXfr/Debug.h>

#include "../../version.h"
ConfigPak::ConfigPak(const Id &id)
    : VarPak(Id("ConfigPak"))
{
    TRACEQFI << id.name()();
}

ConfigPak::ConfigPak(const MultiName &groupName)
    : cmGroupName(groupName)
{

}
