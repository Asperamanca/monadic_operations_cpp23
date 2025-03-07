#include "testcontinuationwriter.h"
#include "../common/printutils.h"
#include "../common/elapsed.h"
#include "../common/sleepy.h"
#include <format>
#include <ranges>
#include <algorithm>
#include <QtConcurrent/qtconcurrentrun.h> // Only this version works in compiler explorer

namespace mop
{

CWriterValueAndTrace<double> CTestContinuationWriter::calculateAreaTraced(const double radius)
{
    return {CSleepy::calculateArea(radius),{std::format("calculateArea with radius {:}", radius),std::source_location::current()}};
}

CWriterValueAndTrace<std::string> CTestContinuationWriter::formatAreaTraced(const double area)
{
    return {CSleepy::formatArea(area),{std::format("formatArea with area {:}", area),std::source_location::current()}};
}

void CTestContinuationWriter::testContinuationWithWriterExternalTrace()
{
    CElapsed logger("ContinuationMonad: testContinuationWithWriterExternalTraceWithObject");

    // We need to add a little glue to put continuation and writer monads together:
    //  1) Creating the writer using makeWriter
    //  2) Wrapping the functions we pass to 'then' using addWriterApi / addWriterApiTraced
    auto future = QtConcurrent::run(makeWriter<double>,5.0)
                        .then(addWriterApiTraced(CSleepy::calculateArea, CTraceEntry{"Trace: calculateArea"}))
                        .then(addWriterApiTraced(CSleepy::formatArea, CTraceEntry("Trace: formatArea")));

    logger.printCheckpoint("AfterCreateFuture");

    auto result = future.result();  // blocks until result is ready - we could also wait for notification asynchronously
    printlnWrapper("Result: {:}\nTrace:", result.getValue());
    printStringRange(result.getTrace(), CTraceEntry::toString);
}

void CTestContinuationWriter::testContinuationWithWriterOwnTrace()
{
    CElapsed logger("ContinuationMonad: testContinuationWithWriterOwnTraceWithObject");

    auto future = QtConcurrent::run(makeWriter<double>,5.0)
                        .then(addWriterApi(calculateAreaTraced))
                        .then(addWriterApi(formatAreaTraced));

    logger.printCheckpoint("AfterCreateFuture");

    auto result = future.result();  // blocks until result is ready - we could also wait for notification asynchronously
    printlnWrapper("Result: {:}\nTrace:", result.getValue());
    printStringRange(result.getTrace(), CTraceEntry::toString);
}

void CTestContinuationWriter::testContinuationSequenceWithWriter()
{
    CElapsed logger("ContinuationMonad: testContinuationSequenceWithWriter");

    std::vector<double> vecInputs{2.0, 3.0, 5.0, 10.0, 12.0};
    auto fMakeFuture = [&](const double input) -> QFuture<CWriter<std::string>>
        {
            return QtConcurrent::run (makeWriter<double>, input)
                                    .then(addWriterApi(calculateAreaTraced))
                                    .then(addWriterApi(formatAreaTraced));
        };

    // We have to create the futures eagerly, otherwise the threads won't start
    // views are lazy, use 'normal' ranges::transform instead
    std::vector<QFuture<CWriter<std::string>>> vecFutures;
    std::ranges::transform(vecInputs, std::back_inserter(vecFutures), fMakeFuture);
    logger.printCheckpoint("AfterCreateFutures");

    // Tag each future with an index, so the printed outputs are distinguishable
    auto resultView = std::views::enumerate(vecFutures);
    for(const auto& [index, future] : resultView)
    {
        auto result = future.result();
        logger.printCheckpoint(std::format("Result {:}: {:}\nTrace:",index, result.getValue()));
        printStringRange(result.getTrace(), CTraceEntry::toString);
    }
}

} // namespace mop

