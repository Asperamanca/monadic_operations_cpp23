#include "benchmarkerrorhandling.h"
#include "errorhandlingutilities.h"
#include "ctrack.hpp"
#include "simulatework.h"

namespace mop
{


int getSizeAfterFilter12345Classic(const std::vector<int>& input)
{
    CTRACK;
    std::size_t out=0;
    for(const int in : input)
    {
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
        // simulateWork();
    }
    return out;
}

int getSizeAfterFilter12345Optional(const std::vector<int>& input)
{
    CTRACK;
    int out = 0;
    for(const int in : input)
    {
        auto oResult = acceptEverythingExceptVOptional<1>(in)
                    .and_then(acceptEverythingExceptVOptional<2>)
                    .and_then(acceptEverythingExceptVOptional<3>)
                    .and_then(acceptEverythingExceptVOptional<4>)
                    .and_then(acceptEverythingExceptVOptional<5>);

        if (oResult.has_value())
        {
            out += *oResult;
            // simulateWork();
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
        try
        {
            auto result = acceptEverythingExceptVException<5>
                          (acceptEverythingExceptVException<4>
                          (acceptEverythingExceptVException<3>
                          (acceptEverythingExceptVException<2>
                          (acceptEverythingExceptVException<1>(in)))));
            out += result;
            // simulateWork();
        }
        catch(int e)
        {
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
        auto oResult = acceptEverythingExceptVExpected<1>(in)
                    .and_then(acceptEverythingExceptVExpected<2>)
                    .and_then(acceptEverythingExceptVExpected<3>)
                    .and_then(acceptEverythingExceptVExpected<4>)
                    .and_then(acceptEverythingExceptVExpected<5>);

        if (oResult.has_value())
        {
            out += *oResult;
            // simulateWork();
        }
    }
    return out;
}

} // namespace mop

