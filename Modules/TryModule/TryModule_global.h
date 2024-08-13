#ifndef TRYMODULE_GLOBAL_H
#define TRYMODULE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TRYMODULE_LIBRARY)
#  define TRYMODULE_EXPORT Q_DECL_EXPORT
#else
#  define TRYMODULE_EXPORT Q_DECL_IMPORT
#endif

#endif // TRYMODULE_GLOBAL_H
