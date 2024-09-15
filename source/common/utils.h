#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <compare>
#include <optional>

class CPoint
{
public:
    int m_X{};
    int m_Y{};
};

template<class F>
concept cIsInvokable = std::is_invocable_v<F>;

std::string convStr(const std::strong_ordering& arg);


class CErrorInfo
{
public:
    CErrorInfo(const std::string& message);

    std::vector<std::string> m_Stack;
    std::string m_Message;
};

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

#endif // UTILS_H

