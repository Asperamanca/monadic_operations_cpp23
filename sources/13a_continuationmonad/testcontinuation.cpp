#include "testcontinuation.h"
#include "../common/printutils.h"
#include "../common/elapsed.h"
#include "../common/sleepy.h"
#include <format>
#include <ranges>
#include <QtConcurrent/qtconcurrentrun.h> // Only this version works in compiler explorer

namespace mop
{

void CTestContinuation::noConcurrency()
{
    CElapsed logger("ContinuationMonad: noConcurrency");

    auto result = CSleepy::formatArea(CSleepy::calculateArea(5.0));
    printlnWrapper("Result: {:}", result);
}

void CTestContinuation::singleValueContinuation()
{
    CElapsed logger("ContinuationMonad: singleValueContinuation");

    auto future = QtConcurrent::run(CSleepy::calculateArea, 5.0)
                      .then(CSleepy::formatArea);
    logger.printCheckpoint("AfterCreateFuture");

    // Normally, we would do other stuff here, subscribe to notification when the result is ready, etc...
    // But to keep it simple, we'll just wait for the result
    auto result = future.result();  // blocks until result is ready
    printlnWrapper("Result: {:}", result);
}

void CTestContinuation::loopNoConcurrenty()
{
    std::vector<double> vecInputs{2.0, 6.0, 9.0};
    CElapsed logger("ContinuationMonad: loopNoConcurrenty");

    auto viewResults = vecInputs
        | std::views::transform(CSleepy::calculateArea)
        | std::views::transform(CSleepy::formatArea);
    logger.printCheckpoint("AfterCreateView");  // This just shows that building the view does not cost much time

    for(const auto& result : viewResults)
    {
        logger.printCheckpoint(std::format("Result: {:}",result));
    }
}

void CTestContinuation::loopContinuation()
{
    //NOTE: I am manually creating a vector of QFutures here, although Qt offers built-in
    //  support for running threads on a sequence (see QtConcurrent::mapped and friends)
    //  However, 'mapped' does not support continuation, and that's what I want to show

    std::vector<double> vecInputs{2.0, 6.0, 9.0};
    CElapsed logger("ContinuationMonad: loopContinuation");

    auto fMakeFuture = [](const double input)
        {
            return QtConcurrent::run(CSleepy::calculateArea, input)
                               .then(CSleepy::formatArea);
        };

    // We have to create the futures eagerly, otherwise the threads won't start
    // views are lazy, use 'normal' ranges::transform instead
    std::vector<QFuture<std::string>> vecFutures;
    std::ranges::transform(vecInputs, std::back_inserter(vecFutures), fMakeFuture);
    logger.printCheckpoint("AfterCreateFutures");   // This shows that not much time has passed

    auto viewResults = vecFutures
                       | std::views::transform([](const auto& future) { return future.result(); });
    logger.printCheckpoint("AfterCreateView");  // Not much time should have passed, either

    for(const auto& result : viewResults)
    {
        logger.printCheckpoint(std::format("Result: {:}",result));
    }
}

} // namespace mop

