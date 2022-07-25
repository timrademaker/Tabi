#include "TabiLogger.h"

#include <spdlog/spdlog.h>

using namespace tabi::logger;

Logger::Logger(const std::string a_LoggerName)
    : m_Logger(std::make_shared<spdlog::logger>(std::string(a_LoggerName.c_str())))
{ }

Logger::Logger(const std::string a_LoggerName, SinkPtr a_Sink)
    : m_Logger(std::make_shared<spdlog::logger>(std::string(a_LoggerName.c_str())))
{
    AddSink(a_Sink);

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

void Logger::Log(ELogLevel a_LogLevel, const char* a_LogMessageFormat, ...) const
{
    va_list args;
    va_start(args, a_LogMessageFormat);
    Log(a_LogLevel, a_LogMessageFormat, args);
    va_end(args);
}

void Logger::Log(ELogLevel a_LogLevel, const char* a_LogMessageFormat, va_list args) const
{
    thread_local tabi::vector<char> buffer(1024);

    DISABLE_WARNING_PUSH
    DISABLE_WARNING(4996)
    const size_t charsWritten = vsprintf(buffer.data(), a_LogMessageFormat, args);
    DISABLE_WARNING_POP

    if (charsWritten > buffer.capacity())
    {
        buffer.resize(charsWritten + 1);
    }

    m_Logger->log(TranslateLogLevel(a_LogLevel), buffer.data());
}

Logger::InternalLogLevel_t Logger::TranslateLogLevel(const ELogLevel a_LogLevel)
{
    return static_cast<InternalLogLevel_t>(a_LogLevel);
}
