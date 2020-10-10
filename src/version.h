// file: ./version.h
#include <eirBase/eirBase_global.h>

#define VER_MAJOR 5
#define VER_MINOR 10
#define VER_RELEASE 1
#define VER_BRANCH 0
#define VER_STRING "v5.10A"
#define VER_TRUNKNAME "develop"
#define VER_MINI  VER_RELEASE
#define VER_MICRO VER_BRANCH
#define VER_BRANCHNAME ""
#define VER_APPVER VER_STRING
#ifndef QT_DEBUG
#define VER_ORGNAME "EclipseIR"
#else
#define VER_ORGNAME "EclipseRD"
#endif

