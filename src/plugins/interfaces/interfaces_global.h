#pragma once

#include <QtCore/qglobal.h>

#if defined(INTERFACES_LIBRARY)
#  define INTERFACES_EXPORT Q_DECL_EXPORT
#else
#  define INTERFACES_EXPORT Q_DECL_IMPORT
#endif
