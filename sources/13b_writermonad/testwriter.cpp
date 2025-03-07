#include "testwriter.h"
#include "writermonad.h"
#include "../common/printutils.h"
#include "../common/sharedfunctions.h"

namespace mop
{

void CTestWriter::testWriterWithoutTrace()
{
    printlnWrapper("testWriterWithoutTrace");

    // Shows that you can just pass function without any tracing
    //  Makes sense mostly if you only want to trace some stages of a pipeline
    auto result = CWriter(5.0)
                  .and_then(calculateArea)
                  .and_then(formatArea);

    printlnWrapper("Result: {:}\nTrace:", result.getValue());
    printStringRange(result.getTrace(), CTraceEntry::toString);
}

void CTestWriter::testWriterWithExternalTrace()
{
    printlnWrapper("testWriterExternalTrace");

    // Shows how to add trace directly when declaring the pipeline
    //  This is very limited in what information you can add, but easy to add
    //  because you don't need to change existing function signatures
    auto result = CWriter(5.0)
                  .and_then(calculateArea, CTraceEntry{"TraceWithSourceLocation", std::source_location::current()})
                  .and_then(formatArea, CTraceEntry{"TraceWithoutSourceLocation"});

    printlnWrapper("Result: {:}\nTrace:", result.getValue());
    printStringRange(result.getTrace(), CTraceEntry::toString);
}

void CTestWriter::testWriterWithOwnTrace()
{
    printlnWrapper("testWriterWithOwnTrace");

    // Function wrappers that return trace information together with the value

    auto fCalculateWithTrace = [](const double radius) -> CWriterValueAndTrace<double>
        {
            auto result = calculateArea(radius);
            return CWriterValueAndTrace(result, CTraceEntry(std::format("Called calculateArea with radius '{:}' and result '{:}'",radius, result), std::source_location::current()));
        };
    auto fFormatWithTrace = [](const double area) -> CWriterValueAndTrace<std::string>
        {
            auto result = formatArea(area);
            return CWriterValueAndTrace(result, CTraceEntry(std::format("Called formatArea with area '{:}' and result '{:}'",area, result), std::source_location::current()));
        };

    // Shows how to utilize the full potential of the writer monad,
    //  with functions that themselves return trace information
    auto result = CWriter(5.0)
                  .and_then(fCalculateWithTrace)
                  .and_then(fFormatWithTrace);

    printlnWrapper("Result: {:}\nTrace:", result.getValue());
    printStringRange(result.getTrace(), CTraceEntry::toString);
}

} // namespace mop
