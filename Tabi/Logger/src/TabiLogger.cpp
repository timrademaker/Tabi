#include "TabiLogger.h"

#include <spdlog/spdlog.h>

using namespace tabi::logger;

Logger::Logger(const tabi::string a_LoggerName)
    : m_Logger(tabi::make_shared<spdlog::logger>(a_LoggerName))
{ }

Logger::Logger(const tabi::string a_LoggerName, SinkPtr a_Sink)
    : m_Logger(tabi::make_shared<spdlog::logger>(a_LoggerName.c_str()))
{
    AddSink(std::move(a_Sink));
}

inline void Logger::AddSink(SinkPtr a_Sink)
{
    m_Logger->sinks().push_back(std::move(a_Sink));
}

void Logger::SetLogLevel(ELogLevel a_LogLevel)
{
    m_Logger->set_level(TranslateLogLevel(a_LogLevel));
}

void Logger::FlushOn(ELogLevel a_LogLevel)
{
    m_FlushOn = a_LogLevel;
    m_Logger->flush_on(TranslateLogLevel(a_LogLevel));
}

void Logger::Log(ELogLevel a_LogLevel, LogMessage_t a_LogMessage) const
{
    m_Logger->log(TranslateLogLevel(a_LogLevel), a_LogMessage);
}

Logger::InternalLogLevel_t Logger::TranslateLogLevel(const ELogLevel a_LogLevel)
{
    return static_cast<InternalLogLevel_t>(a_LogLevel);
}
