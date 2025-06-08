#include "rangesutilities.h"

namespace mop
{

std::vector<int> expandIotaViewsToVector(const std::vector<int>& input)
{
#ifdef __cpp_lib_ranges_to_container
    return std::ranges::to<std::vector>(expandIotaViews(input));
#else
    auto view = expandIotaViews(input);
    std::vector<int> vecResult;
    // vecResult.reserve(view.size()); Does not work, because the view's size cannot be determined cheaply
    for(const auto& value : view)
    {
        vecResult.push_back(value);
    }
    return vecResult;
#endif
}

// Expand all numbers in input to sequences of {1...number}, repeat twice
std::vector<int> expandIotaClassic(const std::vector<int>& input,std::vector<int>&& outVecPrepared)
{
    // std::vector<int> output;
    for(const int i : input)
    {
        for(int q=1;q<=i;++q)
        {
            for(int r=1;r<=q;++r)
            {
                for(int s=1;s<=r;++s)
                {
                    outVecPrepared.push_back(s);
                }
            }
        }
    }
    return outVecPrepared;
}

}

