#ifndef COMPILERINFO_H
#define COMPILERINFO_H

#include <version>

#ifdef __cpp_lib_bind_back
#define MOP_SUPPORTS_BIND_BACK
#endif

#ifdef __cpp_lib_stacktrace
#define MOP_SUPPORTS_STACKTRACE
#endif

#ifdef __cpp_lib_print
#define MOP_SUPPORTS_PRINT
#endif

#ifdef __cpp_lib_ranges_to_container
#define MOP_SUPPORTS_RANGES_TO
#endif


#endif // COMPILERINFO_H
