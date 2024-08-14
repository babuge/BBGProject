#pragma once

#include <QtCore/qglobal.h>

#if defined(TRYMODULE_LIBRARY)
#define TRYMODULE_EXPORT Q_DECL_EXPORT
#else
#define TRYMODULE_EXPORT Q_DECL_IMPORT
#endif
