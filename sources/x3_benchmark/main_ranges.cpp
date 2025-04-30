#include "benchmark.h"
#include "ctrack.hpp"
#include <vector>
#include <numeric>
#include "benchmarkranges.h"


// Make sure to run the benchmark with optimization (-O2 or more)
//  std::ranges::views are terribly slow in debug builds
int main(int argc, char* argv[])
{
    using namespace mop;

    static constexpr std::size_t s_RangesInputLength = 20;
    static constexpr int s_RangesIterations = 200;

    std::vector<int> rangesInput(s_RangesInputLength);
    std::iota(rangesInput.begin(), rangesInput.end(),1);

    benchmark(accumulatePlusMinusExpandedIotaClassic            ,rangesInput,s_RangesIterations);
    benchmark(accumulatePlusMinusExpandedIotaClassicIntegrated  ,rangesInput,s_RangesIterations);
    benchmark(accumulatePlusMinusExpandedIotaViews              ,rangesInput,s_RangesIterations);
    benchmark(accumulatePlusMinusExpandedIotaViewsToVector      ,rangesInput,s_RangesIterations);

    benchmark(findMaxValueIndexInExpandedIotaClassic            ,rangesInput,s_RangesIterations);
    benchmark(findMaxValueIndexInExpandedIotaClassicIntegrated  ,rangesInput,s_RangesIterations);
    benchmark(findMaxValueIndexInExpandedIotaViews              ,rangesInput,s_RangesIterations);
    benchmark(findMaxValueIndexInExpandedIotaViewsToVector      ,rangesInput,s_RangesIterations);

    ctrack::result_print();

    // auto benchmarkResults = ctrack::result_as_string();
    // std::print("{}",benchmarkResults);


    // std::ranges::shuffle(input,gd);

    // std::println("{},{},{},{}",findMaxValueIndexInExpandedIotaClassic(input),
    //                            findMaxValueIndexInExpandedIotaClassicIntegrated(input),
    //                            findMaxValueIndexInExpandedIotaViews(input),
    //                            findMaxValueIndexInExpandedIotaViewsToVector(input));

    // auto outputClassic = expandIotaClassic(input);
    // auto outputView = expandIotaViewsToVector(input);
    // const bool bEqual = std::ranges::equal(outputClassic, outputView);
    // std::println("Ranges equal: {} Size classic: {} Size view: {}",bEqual,outputClassic.size(),outputView.size());

    // auto formatSingle = [](const int value){ return std::format("{};",value);};
    // auto fFormatPair = [](const auto& tuple)
    //     {
    //         const auto&[a,b] = tuple;
    //         return std::format("{} : {}",a,b);
    //     };

    // auto output = std::views::zip(outputClassic,outputView)
    //               | std::views::transform(fFormatPair);

    // auto output = filter12345Exceptions(input);

    // for(const auto& value : input)
    // {
    //     std::println("{}; ",value);
    // }

    // std::println("Output");
    // for(const auto& value : output)
    // {
    //     std::println("{}; ",value);
    // }

    return 0;
}


