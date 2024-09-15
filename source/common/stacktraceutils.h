#ifndef STACKTRACEUTILS_H
#define STACKTRACEUTILS_H

#include "compilerinfo.h"

#ifdef SUPPORTS_STACKTRACE
#include <stacktrace>

std::string formatStacktraceEntry(const std::stacktrace_entry& entry);
std::vector<std::string> formatStacktrace(const std::stacktrace& stacktrace);
void dumpStack(const std::stacktrace& stacktrace);
void dumpStack(const std::vector<std::string>& stackDescription);

#endif // SUPPORTS_STACKTRACE


#endif // STACKTRACEUTILS_H
