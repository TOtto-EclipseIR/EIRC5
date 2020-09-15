#pragma once

#include <QtCore/qglobal.h>

#if defined(EIRFINDER_LIBRARY)
#  define EIRFINDER_EXPORT Q_DECL_EXPORT
#else
#  define EIRFINDER_EXPORT Q_DECL_IMPORT
#endif
