#ifndef SIMULATEWORK_H
#define SIMULATEWORK_H

#include <chrono>
using namespace std::chrono_literals;

static std::chrono::nanoseconds sg_WorkDuration{};

inline void simulateWork()
{
    if (sg_WorkDuration <= 0ns)
    {
        return;
    }

    auto deadline = std::chrono::high_resolution_clock::now() + sg_WorkDuration;

    while (std::chrono::high_resolution_clock::now() < deadline);
}

#endif // SIMULATEWORK_H
