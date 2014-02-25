#ifndef TESTSUITE_GLOBAL_H
#define TESTSUITE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TESTSUITE_LIBRARY)
#  define TESTSUITESHARED_EXPORT Q_DECL_EXPORT
#else
#  define TESTSUITESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // TESTSUITE_GLOBAL_H
