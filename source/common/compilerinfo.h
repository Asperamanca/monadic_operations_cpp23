#ifndef COMPILERINFO_H
#define COMPILERINFO_H

#ifdef _MSC_VER
// MSVC compiler support

#if _MSC_VER >= 1934
#define SUPPORTS_RANGES_TO
#define SUPPORTS_BIND_BACK
#define SUPPORTS_STACKTRACE
#endif

#if _MSC_VER >= 1937
#define SUPPORTS_PRINT
#endif

#elif __llvm__
// LLVM/Clang compiler support

#if __clang_major__ >= 17
#define SUPPORT_RANGES_TO
#endif

#if __clang_major__ >= 18
#define SUPPORTS_PRINT
#endif

#if __clang_major__ >= 19
#define SUPPORTS_BIND_BACK
#endif

#elif __GNUC__
#if __GNUC__ >= 14
#define SUPPORT_RANGES_TO
#define SUPPORTS_BIND_BACK
#define SUPPORTS_PRINT
#endif
#endif


#endif // COMPILERINFO_H
