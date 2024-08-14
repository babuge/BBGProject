#pragma once

#include <QtCore/qglobal.h>

#if defined(PLUGINSMANAGER_LIBRARY)
#define PLUGINSMANAGER_EXPORT Q_DECL_EXPORT
#else
#define PLUGINSMANAGER_EXPORT Q_DECL_IMPORT
#endif
