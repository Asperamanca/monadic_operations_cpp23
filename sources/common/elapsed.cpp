#include "elapsed.h"
#include "printutils.h"

namespace mop
{

CElapsed::CElapsed(std::string name)
    : m_Name(std::move(name)),
      m_Begin(std::chrono::steady_clock::now())
{
    printlnWrapper("{:} - before start", m_Name);
}

CElapsed::~CElapsed()
{
    auto clockDiff = getDiffToBegin(std::chrono::steady_clock::now());
    printlnWrapper("{:} - after end (Elapsed: {:})", m_Name, clockDiff);
}

void CElapsed::printCheckpoint(std::string checkpointName)
{
    auto clockDiff = getDiffToBegin(std::chrono::steady_clock::now());
    printlnWrapper("Checkpoint {:} (Elapsed: {:})", checkpointName, clockDiff);
}

std::chrono::steady_clock::time_point CElapsed::getBegin() const
{
    return m_Begin;
}

std::chrono::milliseconds CElapsed::getDiffToBegin(const std::chrono::steady_clock::time_point& current) const
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(current - m_Begin);
}

} // namespace mop

