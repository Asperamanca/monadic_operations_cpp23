#ifndef COMPILERINFO_H
#define COMPILERINFO_H

#include <version>

#ifdef __cpp_lib_bind_back
#define MOP_SUPPORTS_BIND_BACK
#endif

// Currently only MSVC reliable reports support of stacktrace
// If you have a non-MSVC compiler and you think it supports it, just remove the #ifdef _MSC_VER
#ifdef _MSC_VER
  #ifdef __cpp_lib_stacktrace
  #define MOP_SUPPORTS_STACKTRACE
  #endif
#endif

#ifdef __cpp_lib_print
#define MOP_SUPPORTS_PRINT
#endif

#ifdef __cpp_lib_ranges_to_container
#define MOP_SUPPORTS_RANGES_TO
#endif


#endif // COMPILERINFO_H
