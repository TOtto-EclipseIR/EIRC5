#include "VarMapMap.h"

#include <eirXfr/Debug.h>

VarMapMap::VarMapMap()
{

}

VarMap VarMapMap::value(const MultiName &name) const
{
    NEEDUSE(name);
    TRACE << VarMap().dumpList().join('\n');
    return VarMap();
//    return VarMap::Map::value(name.sortable());
}
