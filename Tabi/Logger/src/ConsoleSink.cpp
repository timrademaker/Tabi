#include "ConsoleSink.h"

#if defined(WINDOWS)
#include <spdlog/sinks/stdout_color_sinks.h>
using sink_type = spdlog::sinks::wincolor_stdout_sink_st;
#else
#include <spdlog/sinks/ansicolor_sink.h>
using sink_type = spdlog::sinks::ansicolor_stdout_sink_st;
#endif

using namespace tabi::logger;

tabi::logger::ConsoleSink::ConsoleSink()
    : m_Sink(tabi::make_unique<sink_type>())
{ 
    m_Sink->set_formatter(std::make_unique<spdlog::pattern_formatter>());
}

void tabi::logger::ConsoleSink::SinkMessage(const SinkMsg_t & a_Message)
{
    m_Sink->log(a_Message);
}

void tabi::logger::ConsoleSink::Flush()
{
    m_Sink->flush();
}
