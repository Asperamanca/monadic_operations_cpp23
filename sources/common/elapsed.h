#ifndef ELAPSED_H
#define ELAPSED_H

#include <string>
#include <chrono>

namespace mop
{

class CElapsed
{
public:
    CElapsed() = delete;
    explicit CElapsed(std::string name);
    ~CElapsed();

    void printCheckpoint(std::string checkpointName);

    std::chrono::steady_clock::time_point getBegin() const;
    std::chrono::milliseconds getDiffToBegin(const std::chrono::steady_clock::time_point& current) const;
private:
    std::string m_Name;
    std::chrono::steady_clock::time_point m_Begin;
};

} // namespace mop

#endif // ELAPSED_H
