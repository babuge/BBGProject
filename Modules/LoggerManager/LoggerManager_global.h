#pragma once

#include <QtCore/qglobal.h>

#if defined(LOGGERMANAGER_LIBRARY)
#  define LOGGERMANAGER_EXPORT Q_DECL_EXPORT
#else
#  define LOGGERMANAGER_EXPORT Q_DECL_IMPORT
#endif
