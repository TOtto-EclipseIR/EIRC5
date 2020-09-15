#include "VersionInfo.h"

#include "../../version.h"

#include "Var.h"

VersionInfo::VersionInfo() : VarMap(QString("VersionInfo")) {;}

VersionInfo VersionInfo::version()
{
    VersionInfo vi;
    vi.insert(Var("Major", EIRC2_VER_MAJOR));
    return vi;
}
