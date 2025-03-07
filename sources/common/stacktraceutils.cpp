#include "stacktraceutils.h"
#include "printutils.h"

#ifdef MOP_SUPPORTS_STACKTRACE
#include <ranges>
#endif // MOP_SUPPORTS_STACKTRACE

namespace mop
{

#ifdef MOP_SUPPORTS_STACKTRACE

std::string formatStacktraceEntry(const std::stacktrace_entry& entry)
{
    return std::format("File: '{:}' Line: '{:}' Description: '{:}",
                       entry.source_file(),entry.source_line(),entry.description());
}

std::vector<std::string> formatStacktrace(const std::stacktrace& stacktrace)
{
    auto strings =  stacktrace
           | std::views::transform(formatStacktraceEntry);
        #ifdef MOP_SUPPORTS_RANGES_TO
            return std::ranges::to<std::vector<std::string>>(strings);
        #else
             return {strings.begin(), strings.end()};
        #endif

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

#endif // MOP_SUPPORTS_STACKTRACE

void log(const std::string& message)
{
    printlnWrapper("Error: {:}", message);

#ifdef MOP_SUPPORTS_STACKTRACE
    dumpStack(std::stacktrace::current());
#else
    printlnWrapper("Your compiler does not support stacktrace");
#endif

} // namespace mop
}
