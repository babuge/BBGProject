#pragma once

#include <QtCore/qglobal.h>

#if defined(BUSSINESSMODULE_LIBRARY)
#define BUSSINESSMODULE_EXPORT Q_DECL_EXPORT
#else
#define BUSSINESSMODULE_EXPORT Q_DECL_IMPORT
#endif
