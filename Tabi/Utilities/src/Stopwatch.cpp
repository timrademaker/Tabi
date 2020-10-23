#include "Stopwatch.h"

#if defined(_DEBUG)
#include <Logging.h>
#include <ConsoleSink.h>

auto swLogger = tabi::logger::CreateTabiLogger<tabi::logger::ConsoleSink>("Stopwatch");
#endif

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
#if defined(_DEBUG)
    else
    {
        swLogger->Log(tabi::logger::ELogLevel::Warning, "Tried to start a stopwatch that was already running!");
    }
#endif
}

void tabi::Stopwatch::Stop()
{
    if (m_IsRunning)
    {
        m_Stop = Now();

        m_IsRunning = false;

        m_AccumulatedTime += std::chrono::duration_cast<nanoseconds>(m_Stop - m_Start);
    }
#if defined(_DEBUG)
    else
    {
        swLogger->Log(tabi::logger::ELogLevel::Warning, "Tried to stop a stopwatch that was not running!");
    }
#endif
}

void tabi::Stopwatch::Reset()
{
    m_AccumulatedTime = nanoseconds();

    m_Start = Now();
    m_Stop = m_Start;
}
