#ifndef COMPILERINFO_H
#define COMPILERINFO_H

#include <version>

#ifdef __cpp_lib_bind_back
#define SUPPORTS_BIND_BACK
#endif

#ifdef __cpp_lib_stacktrace
#define SUPPORTS_STACKTRACE
#endif

#ifdef __cpp_lib_print
#define SUPPORTS_PRINT
#endif

#ifdef __cpp_lib_ranges_to_container
#define SUPPORTS_RANGES_TO
#endif


#endif // COMPILERINFO_H
