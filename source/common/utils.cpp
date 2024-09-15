#include "utils.h"
#include "../common/compilerinfo.h"
#include "../common/stacktraceutils.h"


CErrorInfo::CErrorInfo(const std::string& message)
    :
#ifdef SUPPORTS_STACKTRACE
    m_Stack(formatStacktrace(std::stacktrace::current())),
#else
      m_Stack{{"Your compiler does not support stacktrace"}},
#endif
      m_Message(message)
{
}

std::string convStr(const std::strong_ordering& arg)
{
    return ( (arg < 0)
                ? "<"
                : (arg > 0 ? ">" : "=="));
}
