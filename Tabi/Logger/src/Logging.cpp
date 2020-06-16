#include "Logging.h"

#include "LoggerRegistry.h"

using namespace tabi::logger;

void SetDefaultLogger(LoggerPtr a_Logger)
{
    LoggerRegistry::GetClientLoggerRegistry().SetDefaultLogger(a_Logger);
}

void tabi::logger::Log(ELogLevel a_LogLevel, Logger::LogMessage_t a_Message)
{
    auto logger = LoggerRegistry::GetClientLoggerRegistry().GetDefaultLogger();
    if (logger)
    {
        logger->Log(a_LogLevel, a_Message);
    }
    else
    {
        assert(false && "No default logger has been set!");
    }
}

void tabi::logger::SetDefaultTabiLogger(LoggerPtr a_Logger)
{
    LoggerRegistry::GetTabiLoggerRegistry().SetDefaultLogger(a_Logger);
}

void tabi::logger::TabiLog(ELogLevel a_LogLevel, Logger::LogMessage_t a_Message)
{
    
    auto logger = LoggerRegistry::GetTabiLoggerRegistry().GetDefaultLogger();
    if (logger)
    {
        logger->Log(a_LogLevel, a_Message);
    }
    else
    {
        assert(false && "No default logger has been set!");
    }
}


void tabi::logger::TabiTrace(Logger::LogMessage_t a_Message)
{
    TabiLog(ELogLevel::Trace, a_Message);
}

void tabi::logger::TabiDebug(Logger::LogMessage_t a_Message)
{
    TabiLog(ELogLevel::Debug, a_Message);
}

void tabi::logger::TabiInfo(Logger::LogMessage_t a_Message)
{
    TabiLog(ELogLevel::Info, a_Message);
}

void tabi::logger::TabiWarn(Logger::LogMessage_t a_Message)
{
    TabiLog(ELogLevel::Warning, a_Message);
}

void tabi::logger::TabiError(Logger::LogMessage_t a_Message)
{
    TabiLog(ELogLevel::Error, a_Message);
}

void tabi::logger::TabiCritical(Logger::LogMessage_t a_Message)
{
    TabiLog(ELogLevel::Critical, a_Message);
}