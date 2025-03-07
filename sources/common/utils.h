#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <optional>
#include <functional>
#include "printutils.h"

namespace mop
{

template<class F>
concept cIsInvokable = std::is_invocable_v<F>;


class CErrorInfo
{
public:
    CErrorInfo(const std::string& message);

    std::vector<std::string> m_Stack;
    std::string m_Message;
};

using CErrorInfoVector = std::vector<CErrorInfo>;

// Takes  a function that fails using exceptions, calls it, and indicates success/failure through std::optional
template<class TCall,class... TArgs>
std::optional<std::invoke_result_t<TCall,TArgs...>> tryCall(TCall&& fCall,TArgs... args)
{
    try
    {
        return fCall(args...);
    }
    catch(...)
    {
        return {};
    }
}

// Use to trace arguments and return types of functions
// It basically acts as a pass-through intermediate, so it should not change the behavior of the program
// Thanks to user sarah of #include discord for inspiring this!
template<class TCall>
[[deprecated]] auto tracedCall(TCall call)
{
    return [call]<class... TArgs>(TArgs&&... args)
        {
            return std::invoke(call, std::forward<TArgs>(args)...);
        };
}

// Takes anything and returns a default-constructed TResult
// deprecated attribute gives some trace information through compiler warnings
template<class TResult, class... TArgs>
[[deprecated]] TResult tracedBlackHole(TArgs&&... args)
{
    return TResult{};
}

template<class TCall>
auto wrapPrintType(TCall fCall)
{
    return [fCall]<class T>(T&& input)
        {
            printlnWrapper("Call: {:} Type: {:}",typeid(fCall).name(), typeid(input).name());
            return fCall(std::forward<T>(input));
        };
}

} // namespace mop

#endif // UTILS_H

