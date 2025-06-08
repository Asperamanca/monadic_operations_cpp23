#include "ctrack.hpp"
#include "benchmarkerrorhandling.h"
#include "benchmark.h"
#include "simulatework.h"
#include "configureerrorhandling.h"
#include "parsecommandline.h"

using namespace std::chrono_literals;

namespace mop
{

// BENCHMARK FOR ERROR HANDLING
// An input value is passed into a function with 5 gates
//  Each gate accepts everything BUT a certain value:
//   - Gate 1 rejects '1' but accepts any other number
//   - Gate 2 rejects '2' but accepts any other number
// ...and so on
//  If a value is accepted, it is forwarded to the next gate
//  This is repeated for a number of input values and iterations (see "configureerrorhandling.h")
//
// Because of the way the gates are configured, you can create a random sequence of numbers with a
//  statistically clear rejection rate:
//  Just choose the desired ration between numbers 1 to 5 (rejected) and numbers above 5 (accepted)
// So, an all happy-path run will have (different) numbers 6 or higher
// And all-sad-path run will have numbers 1 to 5
// A 50:50 happy/sad path run will have an equal distribution of numbers 1 to 10
//
// The different implementations are:
//  1: Baseline (only simulated work, no error handling)
//  2: Value-based: bool returned from function indicates success or failure
//  3: std::expected with and_then
//  4: std::optional with and_then
//  5: Exceptions
//
// Via command line, please choose:
//  - the test to run (1st argument: just the number, nothing else)
//  - the rejection rate in per mille (1/1000) - some numbers will be adjusted to the next representable value
//      (look at the output)

std::optional<std::vector<int>> generateInitialInput(const int rejectionPermille)
{
    auto oDistribution = [rejectionPermille]() -> std::optional<std::uniform_int_distribution<int>>
        {
            if ((rejectionPermille < 0) || (rejectionPermille > 1000))
            {
                return {};
            }

            if (rejectionPermille == 0)
            {
                std::cout << std::format("Chosen distribution range: '6' to '100', equivalent to total rejection rate of '0' permille\n");
                return std::uniform_int_distribution<int>{6,100};
            }

            const int rangeTo = 5000 / rejectionPermille;
            std::cout << std::format("Chosen distribution range: '{}' to '{}', equivalent to total rejection rate of '{}' permille\n",1, rangeTo, 5000 / rangeTo);
            return std::uniform_int_distribution<int>{1,rangeTo};
        }();

    return oDistribution.transform([](std::uniform_int_distribution<int> dist)
        {
            std::random_device rd;
            std::mt19937 gd{rd()};
            auto fGenRnd = [&](){ return dist(gd);};
            std::vector<int> vector(s_ErrorHandlingInputLength);
            std::ranges::generate(vector,fGenRnd);
            return vector;
        });
}

} // namespace mop

// Make sure to run the benchmark with optimization (-O2 or more)
int main(int argc, char* argv[])
{
    using namespace mop;

    static constexpr auto s_IncorrectTestNumberMessage = "Please specify test number (1st argument: 1 to 5):\n"
                                                         "1: Baseline (only simulated work, no error handling)\n"
                                                         "2: Value-based: bool returned from function indicates success or failure\n"
                                                         "3: std::expected with and_then \n"
                                                         "4: std::optional with and_then\n"
                                                         "5: Exceptions\n";

    const auto oTestNumber = getNumberFromCmdLine(argc, argv, 1);
    if ( ! oTestNumber )
    {
        std::cout << s_IncorrectTestNumberMessage;
        return 1;
    }

    const auto oRejectionPermille = getNumberFromCmdLine(argc, argv, 2);
    if ( ! oRejectionPermille )
    {
        std::cout << "Please specify total rejection in permille (2nd argument: 0...1000)\n";
        return 1;
    }

    auto oErrorHandlingInput = generateInitialInput(*oRejectionPermille);
    if ( ! oErrorHandlingInput)
    {
        std::cout << std::format("Rejection permille '{}' is not representable\n",*oRejectionPermille);
        return 1;
    }

    // Configure benchmark in configureerrorhandling.h
    seedWorkHash(s_ErrorHandlingInputLength);

    switch (*oTestNumber)
    {
        case 1: benchmark("Errorhandling_Baseline"  ,getSizeAfterFilter12345Baseline   ,*oErrorHandlingInput,s_ErrorHandlingIterations); break;
        case 2: benchmark("Errorhandling_ValueBased",getSizeAfterFilter12345ValueBased ,*oErrorHandlingInput,s_ErrorHandlingIterations); break;
        case 3: benchmark("Errorhandling_Expected"  ,getSizeAfterFilter12345Expected   ,*oErrorHandlingInput,s_ErrorHandlingIterations); break;
        case 4: benchmark("Errorhandling_Optional"  ,getSizeAfterFilter12345Optional   ,*oErrorHandlingInput,s_ErrorHandlingIterations); break;
        case 5: benchmark("Errorhandling_Exceptions",getSizeAfterFilter12345Exceptions ,*oErrorHandlingInput,s_ErrorHandlingIterations); break;
        default:
        {
            std::cout << s_IncorrectTestNumberMessage;
            return 1;
        }
    }

    std::cout << getHashAccumulatedResult() << "\n";
    ctrack::result_print();

    return 0;
}



