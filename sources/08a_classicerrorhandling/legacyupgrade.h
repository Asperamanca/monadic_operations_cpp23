#ifndef LEGACYUPGRADE_H
#define LEGACYUPGRADE_H

#include <optional>

namespace mop
{


// Adapter function to allow 'classic' functions participate within an optional pipeline.
//  Expects the original function to
//  1) Return success information via 'bool' retval
//  2) Provide actual value via last byref out param
// Takes that function and any arguments, and returns an optional which combines
//  success information and actual value
template<class TRet, class TFunc, class... TArgs>
requires std::is_invocable_v<TFunc,TArgs...,TRet&> &&
         std::is_same_v<bool, std::invoke_result_t<TFunc,TArgs...,TRet&>>
std::optional<TRet> convertOutParamToOptional(TFunc f, TArgs&& ...args)
{
    // Prepare value on the stack
    TRet r;
    // Call function, ask to fill 'r'
    if (f(std::forward<TArgs>(args)...,r))
    {
        // Succeeded
        // Will fall back to copying if move is unavailable
        return {std::move(r)};
    }
    // Failed
    return {};
}

// Convenience wrapper around convertOutParamToOptional, so you can create
//  new functions which return optional from existing ones which don't
template<class TRet, class TFunc>
auto wrapOutParamToOptional(TFunc f)
{
    return [f]<class... TArgs>(TArgs&& ...args) -> std::optional<TRet>
        {
            return convertOutParamToOptional<TRet, TFunc, TArgs...>(f,std::forward<TArgs>(args)...);
        };
}

} // namespace mop

#endif // LEGACYUPGRADE_H
