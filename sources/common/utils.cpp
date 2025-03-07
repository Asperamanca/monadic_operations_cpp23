#include "utils.h"
#include "../common/compilerinfo.h"
#include "../common/stacktraceutils.h"

namespace mop
{

CErrorInfo::CErrorInfo(const std::string& message)
    :
#ifdef MOP_SUPPORTS_STACKTRACE
    m_Stack(formatStacktrace(std::stacktrace::current())),
#else
      m_Stack{{"Your compiler does not support stacktrace"}},
#endif
      m_Message(message)
{
}

} // namespace mop
