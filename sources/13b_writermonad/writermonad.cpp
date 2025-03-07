#include "writermonad.h"
#include <format>

namespace mop
{

CTraceEntry::CTraceEntry(std::string message)
    : m_Message(message)
{
}

CTraceEntry::CTraceEntry(std::string message,std::source_location location)
    : m_Message(message),
      m_SourceLocation(location)
{
}

std::string CTraceEntry::toString(const CTraceEntry& traceEntry)
{
    return std::format("{:} @ {:}", traceEntry.m_Message, traceEntry.m_SourceLocation.function_name());
}

TraceVector concatTrace(TraceVector first, TraceVector second)
{
    TraceVector resultVec{std::move(first)};
    std::move(second.begin(), second.end(), std::back_inserter(resultVec));
    return resultVec;
}

} // namespace mop

