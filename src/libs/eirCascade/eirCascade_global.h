#pragma once

#include <QtCore/qglobal.h>

#if defined(EIRCASCADE_LIBRARY)
#  define EIRCASCADE_EXPORT Q_DECL_EXPORT
#else
#  define EIRCASCADE_EXPORT Q_DECL_IMPORT
#endif
