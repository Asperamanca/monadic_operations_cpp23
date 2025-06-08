#ifndef CONFIGUREERRORHANDLING_H
#define CONFIGUREERRORHANDLING_H

#include <cstddef>

// Set to '1' if you want to do a piece of simulated work before entering gate 1
#define MOP_BENCHMARK_ERRORHANDLING_SIMULATE_WORK_BEFORE    1
// Set to '1' if you want to do a piece of simulated work after exiting gate 5 (with success)
#define MOP_BENCHMARK_ERRORHANDLING_SIMULATE_WORK_AFTER     0


namespace mop
{

// Number of inputs, each gets passed through up to 5 gates (less if rejected) per iteration
static constexpr std::size_t s_ErrorHandlingInputLength = 10000;
// Number of iterations of the test run
static constexpr int s_ErrorHandlingIterations = 100;

} // namespace mop


#endif // CONFIGUREERRORHANDLING_H
