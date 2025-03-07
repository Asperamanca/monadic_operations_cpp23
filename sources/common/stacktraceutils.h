#ifndef STACKTRACEUTILS_H
#define STACKTRACEUTILS_H

#include "compilerinfo.h"
#include <vector>
#include <string>

#ifdef MOP_SUPPORTS_STACKTRACE
#include <stacktrace>
#endif // MOP_SUPPORTS_STACKTRACE

namespace mop
{

#ifdef MOP_SUPPORTS_STACKTRACE

std::string formatStacktraceEntry(const std::stacktrace_entry& entry);
std::vector<std::string> formatStacktrace(const std::stacktrace& stacktrace);
void dumpStack(const std::stacktrace& stacktrace);
void dumpStack(const std::vector<std::string>& stackDescription);

#endif // MOP_SUPPORTS_STACKTRACE

void log(const std::string& message);

} // namespace mop

#endif // STACKTRACEUTILS_H
