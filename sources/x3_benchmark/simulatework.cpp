#include "simulatework.h"
#include <algorithm>
#include <iterator>
#include <unordered_map>
#include <random>
using namespace std::chrono_literals;

namespace mop
{

static std::chrono::nanoseconds sg_WorkDuration{};

void setWorkDuration(std::chrono::nanoseconds duration)
{
    sg_WorkDuration = duration;
}

void simulateWorkByTimer()
{
    if (sg_WorkDuration <= 0ns)
    {
        return;
    }

    auto deadline = std::chrono::high_resolution_clock::now() + sg_WorkDuration;

    while (std::chrono::high_resolution_clock::now() < deadline);
}

static std::unordered_map<int,int> sg_WorkHash{};
static long long int sg_WorkHashAccumulatedResult{};

void seedWorkHash(std::size_t size)
{
    std::random_device rd;
    std::mt19937 gd{rd()};
    std::uniform_int_distribution<int> values{1,2};
    sg_WorkHashAccumulatedResult = 0LL;

    int i=0;
    auto fGenRnd = [&](){ return std::make_pair(i++,values(gd));};

    sg_WorkHash.clear();
    for(std::size_t s=0; s<size;++s)
    {
        sg_WorkHash.insert(fGenRnd());
    }
}


void simulateWorkByHashLookup(const int key)
{
    auto iter = sg_WorkHash.find(key);
    if (iter == sg_WorkHash.end())
    {
        return;
    }
    sg_WorkHashAccumulatedResult += iter->second;
}

long long getHashAccumulatedResult()
{
    return sg_WorkHashAccumulatedResult;
}



} // namespace mop


