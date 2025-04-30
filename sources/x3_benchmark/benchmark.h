#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <algorithm>
#include <format>
#include <iostream>
#include <random>
#include <vector>

namespace mop
{

template<class TCall>
void benchmark(TCall&& fCall, const std::vector<int>& input, const int iterations)
{
    std::random_device rd;
    std::mt19937 gd{rd()};

    using TResult = std::invoke_result_t<TCall, decltype(input)>;
    std::vector<TResult> singleResults;
    singleResults.reserve(iterations);
    auto currentInput = input;
    // All the shuffle, collecting a result and outputting it is mostly to prevent the compiler from optimizing away everything
    for(int i=0;i<iterations;++i)
    {
        singleResults.push_back(fCall(currentInput));
        std::ranges::shuffle(currentInput, gd);
    }
    auto sum = std::ranges::fold_left(singleResults,0,std::plus<>());
    double avg = static_cast<double>(sum) / static_cast<double>(singleResults.size());
    std::cout << std::format("Input size: {}",input.size()) << "\n";
    std::cout << std::format("Avg result: {}",avg) << "\n";
}

} // namespace mop

#endif // BENCHMARK_H
