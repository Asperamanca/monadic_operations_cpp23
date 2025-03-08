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
    m_Stack{{"Stacktrace is not enabled. If you believe your compiler supports it, please enable in compierinfo.h"}},
#endif
    m_Message(message)
{
}

} // namespace mop
