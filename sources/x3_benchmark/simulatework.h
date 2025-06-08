#ifndef SIMULATEWORK_H
#define SIMULATEWORK_H

#include <chrono>

namespace mop
{

// Functions to simulate some work, to get a perspective how much influence the
//  performance differences of various test cases would have on someting closer to real code
// (branching or loops for the sake of it are rarely the only things you do in real code)
// All functions here for single-threaded use only

void setWorkDuration(std::chrono::nanoseconds duration);
void simulateWorkByTimer();

void seedWorkHash(std::size_t size);
void simulateWorkByHashLookup(const int key);
long long int getHashAccumulatedResult();

} // namespace mop

#endif // SIMULATEWORK_H
