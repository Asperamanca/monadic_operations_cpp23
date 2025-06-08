#include "benchmarkerrorhandling.h"
#include "errorhandlingutilities.h"
#include "ctrack.hpp"
#include "simulatework.h"
#include "configureerrorhandling.h"

namespace mop
{

int getSizeAfterFilter12345Baseline(const std::vector<int>& input)
{
    CTRACK;
    for(const int in : input)
    {
#if MOP_BENCHMARK_ERRORHANDLING_SIMULATE_WORK_BEFORE
        simulateWorkByHashLookup(in);
#endif
        if (in <= 5)
        {
            continue;
        }
#if MOP_BENCHMARK_ERRORHANDLING_SIMULATE_WORK_AFTER
        simulateWorkByHashLookup(in);
#endif
    }
    return 0;
}


int getSizeAfterFilter12345ValueBased(const std::vector<int>& input)
{
    CTRACK;
    int out=0;
    for(const int in : input)
    {
#if MOP_BENCHMARK_ERRORHANDLING_SIMULATE_WORK_BEFORE
        simulateWorkByHashLookup(in);
#endif
        int a;
        if ( ! acceptEverythingExceptVClassic<1>(in,a))
        {
            continue;
        }
        int b;
        if ( ! acceptEverythingExceptVClassic<2>(a,b))
        {
            continue;
        }
        int c;
        if ( ! acceptEverythingExceptVClassic<3>(b,c))
        {
            continue;
        }
        int d;
        if ( ! acceptEverythingExceptVClassic<4>(c,d))
        {
            continue;
        }
        int e;
        if ( ! acceptEverythingExceptVClassic<5>(d,e))
        {
            continue;
        }

        out += e;
#if MOP_BENCHMARK_ERRORHANDLING_SIMULATE_WORK_AFTER
        simulateWorkByHashLookup(in);
#endif
    }
    return out;
}

int getSizeAfterFilter12345Optional(const std::vector<int>& input)
{
    CTRACK;
    int out = 0;
    for(const int in : input)
    {
#if MOP_BENCHMARK_ERRORHANDLING_SIMULATE_WORK_BEFORE
        simulateWorkByHashLookup(in);
#endif
        auto oResult = acceptEverythingExceptVOptional<1>(in)
                    .and_then(acceptEverythingExceptVOptional<2>)
                    .and_then(acceptEverythingExceptVOptional<3>)
                    .and_then(acceptEverythingExceptVOptional<4>)
                    .and_then(acceptEverythingExceptVOptional<5>);

        if (oResult.has_value())
        {
            out += *oResult;
#if MOP_BENCHMARK_ERRORHANDLING_SIMULATE_WORK_AFTER
            simulateWorkByHashLookup(in);
#endif
        }
    }
    return out;
}

int getSizeAfterFilter12345Exceptions(const std::vector<int>& input)
{
    CTRACK;
    int out = 0;
    for(const int in : input)
    {
#if MOP_BENCHMARK_ERRORHANDLING_SIMULATE_WORK_BEFORE
        simulateWorkByHashLookup(in);
#endif
        try
        {
            auto result = acceptEverythingExceptVException<5>
                          (acceptEverythingExceptVException<4>
                          (acceptEverythingExceptVException<3>
                          (acceptEverythingExceptVException<2>
                          (acceptEverythingExceptVException<1>(in)))));
            out += result;
#if MOP_BENCHMARK_ERRORHANDLING_SIMULATE_WORK_AFTER
            simulateWorkByHashLookup(in);
#endif
        }
        catch(int e)
        {
            std::ignore = e;
        }
    }
    return out;
}

int getSizeAfterFilter12345Expected(const std::vector<int>& input)
{
    CTRACK;
    int out = 0;
    for(const int in : input)
    {
#if MOP_BENCHMARK_ERRORHANDLING_SIMULATE_WORK_BEFORE
        simulateWorkByHashLookup(in);
#endif
        auto oResult = acceptEverythingExceptVExpected<1>(in)
                    .and_then(acceptEverythingExceptVExpected<2>)
                    .and_then(acceptEverythingExceptVExpected<3>)
                    .and_then(acceptEverythingExceptVExpected<4>)
                    .and_then(acceptEverythingExceptVExpected<5>);

        if (oResult.has_value())
        {
            out += *oResult;
#if MOP_BENCHMARK_ERRORHANDLING_SIMULATE_WORK_AFTER
            simulateWorkByHashLookup(in);
#endif
        }
    }
    return out;
}




} // namespace mop

