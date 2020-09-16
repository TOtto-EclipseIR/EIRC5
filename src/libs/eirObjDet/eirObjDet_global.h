#pragma once

#include <QtCore/qglobal.h>

#if defined(EIROBJDET_LIBRARY)
#  define EIROBJDET_EXPORT Q_DECL_EXPORT
#else
#  define EIROBJDET_EXPORT Q_DECL_IMPORT
#endif
