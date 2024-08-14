#pragma once

#include <QtCore/qglobal.h>

#if defined(MODULESMANAGER_LIBRARY)
#define MODULESMANAGER_EXPORT Q_DECL_EXPORT
#else
#define MODULESMANAGER_EXPORT Q_DECL_IMPORT
#endif
