#ifndef POSTGRESSTEST_GLOBAL_H
#define POSTGRESSTEST_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(POSTGRESSTEST_LIBRARY)
#  define POSTGRESSTESTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define POSTGRESSTESTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // POSTGRESSTEST_GLOBAL_H
