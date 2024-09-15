#include "stacktraceutils.h"

#ifdef SUPPORTS_STACKTRACE

#include "printutils.h"
#include <ranges>

std::string formatStacktraceEntry(const std::stacktrace_entry& entry)
{
    return std::format("File: '{:}' Line: '{:}' Description: '{:}",
                       entry.source_file(),entry.source_line(),entry.description());
}

std::vector<std::string> formatStacktrace(const std::stacktrace& stacktrace)
{
    return stacktrace
           | std::views::transform(formatStacktraceEntry)
           | std::ranges::to<std::vector<std::string>>();
}

void dumpStack(const std::stacktrace& stacktrace)
{
    dumpStack(formatStacktrace(stacktrace));
}

void dumpStack(const std::vector<std::string>& stackDescription)
{
    for(const auto& entry : stackDescription)
    {
        printlnWrapper("{:}",entry);
    }
}

#endif // SUPPORTS_STACKTRACE

