#ifndef BENCHMARKERRORHANDLING_H
#define BENCHMARKERRORHANDLING_H

#include <vector>

namespace mop
{

// These are the main, benchmarked functions

int getSizeAfterFilter12345Baseline(const std::vector<int>& input);
int getSizeAfterFilter12345ValueBased(const std::vector<int>& input);
int getSizeAfterFilter12345Optional(const std::vector<int>& input);
int getSizeAfterFilter12345Exceptions(const std::vector<int>& input);
int getSizeAfterFilter12345Expected(const std::vector<int>& input);

}

#endif // BENCHMARKERRORHANDLING_H
