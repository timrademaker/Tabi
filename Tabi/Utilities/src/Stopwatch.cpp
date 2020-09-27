#include "Stopwatch.h"

tabi::Stopwatch::Stopwatch(bool a_StartRunning)
    : m_Start(Now())
    , m_Stop(m_Start)
    , m_AccumulatedTime(0)
    , m_IsRunning(false)
{
    if (a_StartRunning)
    {
        Start();
    }
}

void tabi::Stopwatch::Start()
{
    if (!m_IsRunning)
    {
        m_IsRunning = true;

        m_Start = Now();
        m_Stop = m_Start;
    }
}

void tabi::Stopwatch::Stop()
{
    if (m_IsRunning)
    {
        m_Stop = Now();

        m_IsRunning = false;

        m_AccumulatedTime += std::chrono::duration_cast<nanoseconds>(m_Stop - m_Start);
    }
}

void tabi::Stopwatch::Reset()
{
    m_AccumulatedTime = nanoseconds();

    m_Start = std::chrono::high_resolution_clock::now();
    m_Stop = m_Start;
}
