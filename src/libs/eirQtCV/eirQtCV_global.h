#pragma once

#include <QtCore/qglobal.h>

#if defined(EIRQTCV_LIBRARY)
#  define EIRQTCV_EXPORT Q_DECL_EXPORT
#else
#  define EIRQTCV_EXPORT Q_DECL_IMPORT
#endif
