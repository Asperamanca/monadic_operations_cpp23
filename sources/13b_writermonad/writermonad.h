#ifndef WRITERMONAD_H
#define WRITERMONAD_H

#include <string>
#include <vector>
#include <utility>
#include <functional>
#include <algorithm>
#include <source_location>
#include "../common/printutils.h"

namespace mop
{

// Note on the implementation: Uses mostly value parameters for simplicity.
//  The goal of this code is to show how a writer monad works. This is not optimized, production-ready code


// A single trace entry containing a message and a source location
struct CTraceEntry
{
    std::string m_Message{};
    std::source_location m_SourceLocation{};

    // Implicit conversion allows creating CTraceEntry directly from std::string
    CTraceEntry(std::string message);
    CTraceEntry(std::string message, std::source_location location);

    static std::string toString(const CTraceEntry& traceEntry);
};

// For simplicity we use a plain vector of trace entries
using TraceVector = std::vector<CTraceEntry>;

TraceVector concatTrace(TraceVector first, TraceVector second);

// Wrapper return type for functions returning both a value and trace information
template<class T>
struct CWriterValueAndTrace
{
    using ValueType = T;

    T m_Value{};
    TraceVector m_Trace{};

    // Default constructor simplifies handling in some contexts
    CWriterValueAndTrace() = default;

    // Implicit conversion allows creating CWriterValueAndTrace from value alone (m_Trace is empty)
    CWriterValueAndTrace(T value);

    // Create from value and CTraceEntry
    CWriterValueAndTrace(T value, CTraceEntry trace);

    // Create from value and TraceVector
    CWriterValueAndTrace(T value, TraceVector traceVector);
};

template<class T>
inline CWriterValueAndTrace<T>::CWriterValueAndTrace(T value)
    : m_Value(std::move(value))
{
}

template<class T>
inline CWriterValueAndTrace<T>::CWriterValueAndTrace(T value, CTraceEntry trace)
    : m_Value{std::move(value)},
      m_Trace{std::move(trace)}
{
}

template<class T>
inline CWriterValueAndTrace<T>::CWriterValueAndTrace(T value, TraceVector traceVector)
    : m_Value{std::move(value)},
      m_Trace{std::move(traceVector)}
{
}

// Allows me to check whether a template argument is a CWriterValueAndTrace
template<class> constexpr bool cIsWriterValueAndTrace = false;
template<class T> constexpr bool cIsWriterValueAndTrace<CWriterValueAndTrace<T>> = true;



// Writer monad impelemntation
// Wrap initial value, then use "and_then" for further steps in the pipeline
template<class TValue>
class CWriter
{
public:
    CWriter() = default;
    explicit CWriter(TValue initialValue);
    // You can initialize a writer with an initial vector of trace entries, too
    explicit CWriter(TValue initialValue, TraceVector trace);

    TValue getValue() const;
    TraceVector getTrace() const;

    // Call the next function in a chain.
    // Overload for functions which
    //  a) already return trace information via CWriterValueAndTrace
    //  b) do not need to be traced
    template<class TCall>
    auto and_then(TCall&& fInvoke) const;

    // Call the next function in a chain.
    // Overload for functions which do not offer trace information themselves
    // Trace information is provided via 'trace' parameter
    template<class TCall>
    auto and_then(TCall&& fInvoke, const CTraceEntry& trace) const;

private:
    TValue m_Value{};
    TraceVector m_Trace{};
};

// Factory method: Useful as adapter when using within other monadic operations (such as continuation)
template<class TValue>
inline CWriter<TValue> makeWriter(TValue value)
{
    return CWriter<TValue>(value);
}

// Returns a new function that accepts a CWriter as input, and invokes and_then on it
//  Needed as adapter when using the writer within other monadic operations (such as continuation)
// For functions which
//  a) already return trace information via CWriterValueAndTrace
//  b) do not need to be traced
// NOTE: Pass and capture by value might cause unnecessary copies when passing e.g. function objects,
//  but is a safe and simple way. Since this is about combining monads, not the intricacies of perfect forwarding,
//  I don't want to use a more complicated solution here
template<class TCall>
inline auto addWriterApi(TCall fInvoke)
{
    return [fInvoke]<class TValue>(const CWriter<TValue>& in)
    {
        return in.and_then(fInvoke);
    };
}

// Here is a more advanced version, if your compiler supports 'deduce this'
//  We could do the same for addWriterApiTraced
// template<class TCall>
// inline auto addWriterApi(TCall&& fInvoke)
// {
//     return [fInvoke2 = std::forward<TCall>(fInvoke)]<class TValue>(this auto&& self, const CWriter<TValue>& in)
//     {
//         return in.and_then(std::forward_like<decltype(self)>(fInvoke2));
//     };
// }

// Returns a new function that accepts a CWriter as input, and invokes and_then on it
// For functions which do not offer trace information themselves
// Trace information is provided via 'trace' parameter
template<class TCall>
inline auto addWriterApiTraced(TCall fInvoke, const CTraceEntry& trace)
{
    return [fInvoke, trace]<class TValue>(const CWriter<TValue>& in)
    {
        return in.and_then(fInvoke, trace);
    };
}



template<class TValue>
template<class TCall>
inline auto CWriter<TValue>::and_then(TCall&& fInvoke) const
{
    using TRet = std::invoke_result_t<TCall, TValue>;

    if constexpr (cIsWriterValueAndTrace<TRet>)
    {
        // Branch for functions that return their own trace through CWriterValueAndTrace
        auto newValueWithTrace = std::invoke(std::forward<TCall>(fInvoke), m_Value);
        using TNewValue = TRet::ValueType;
        return CWriter<TNewValue>(newValueWithTrace.m_Value, concatTrace(m_Trace, newValueWithTrace.m_Trace));
    }
    else
    {
        // Branch for functions that don't provide tracing information
        // Forward without adding trace
        auto newValue = std::invoke(std::forward<TCall>(fInvoke), m_Value);
        return CWriter<decltype(newValue)>(newValue, m_Trace);
    }
}

template<class TValue>
template<class TCall>
inline auto CWriter<TValue>::and_then(TCall&& fInvoke, const CTraceEntry& trace) const
{
    using TRet = std::invoke_result_t<TCall, TValue>;

    if constexpr (cIsWriterValueAndTrace<TRet>)
    {
        static_assert(false,"Function already returns trace information - use overload of and_then without trace parameter!");
    }
    else
    {
        // Add 'trace' from parameter
        auto newValue = std::invoke(std::forward<TCall>(fInvoke), m_Value);
        return CWriter<decltype(newValue)>(newValue, concatTrace(m_Trace, {trace}));
    }
}


template<class TValue>
inline CWriter<TValue>::CWriter(TValue initialValue)
    : m_Value(std::move(initialValue))
{
}

template<class TValue>
inline CWriter<TValue>::CWriter(TValue initialValue, TraceVector trace)
    : m_Value(std::move(initialValue)),
      m_Trace(std::move(trace))
{
}

template<class TValue>
inline TValue CWriter<TValue>::getValue() const
{
    return m_Value;
}

template<class TValue>
inline TraceVector CWriter<TValue>::getTrace() const
{
    return m_Trace;
}


} // namespace mop

#endif // WRITERMONAD_H
