#include "benchmark.h"
#include "ctrack.hpp"
#include "benchmarkerrorhandling.h"
#include "simulatework.h"

// Make sure to run the benchmark with optimization (-O2 or more)
//  std::ranges::views are terribly slow in debug builds
int main(int argc, char* argv[])
{
    using namespace mop;

    // sg_WorkDuration = 10us;

    static constexpr std::size_t s_ErrorHandlingInputLength = 1000;
    static constexpr int s_ErrorHandlingIterations = 1000;

    std::vector<int> errorHandlingInput(s_ErrorHandlingInputLength);

    std::random_device rd;
    std::mt19937 gd{rd()};
    std::uniform_int_distribution<int> dist{1,50};
    auto fGenRnd = [&](){ return dist(gd);};
    std::ranges::generate(errorHandlingInput,fGenRnd);

    benchmark(getSizeAfterFilter12345Classic    ,errorHandlingInput,s_ErrorHandlingIterations);
    benchmark(getSizeAfterFilter12345Expected   ,errorHandlingInput,s_ErrorHandlingIterations);
    benchmark(getSizeAfterFilter12345Optional   ,errorHandlingInput,s_ErrorHandlingIterations);
    benchmark(getSizeAfterFilter12345Exceptions ,errorHandlingInput,s_ErrorHandlingIterations);

    ctrack::result_print();

    return 0;
}


