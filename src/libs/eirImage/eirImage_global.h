#pragma once

#include <QtCore/qglobal.h>

#if defined(EIRIMAGE_LIBRARY)
#  define EIRIMAGE_EXPORT Q_DECL_EXPORT
#else
#  define EIRIMAGE_EXPORT Q_DECL_IMPORT
#endif
