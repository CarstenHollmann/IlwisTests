#ifndef RASTEROPERATIONSTEST_GLOBAL_H
#define RASTEROPERATIONSTEST_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(RASTEROPERATIONSTEST_LIBRARY)
#  define RASTEROPERATIONSTESTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define RASTEROPERATIONSTESTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // RASTEROPERATIONSTEST_GLOBAL_H