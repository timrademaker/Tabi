#include "Logging.h"

#include "LoggerRegistry.h"

using namespace tabi::logger;

void tabi::logger::SetDefaultLogger(LoggerPtr a_Logger)
{
    LoggerRegistry::GetClientLoggerRegistry().SetDefaultLogger(a_Logger);
}

void tabi::logger::Log(ELogLevel a_LogLevel, const char* a_Message, ...)
{
    auto logger = LoggerRegistry::GetClientLoggerRegistry().GetDefaultLogger();
    if (logger)
    {
        va_list args;
        va_start(args, a_Message);
        logger->Log(a_LogLevel, a_Message, args);
        va_end(args);
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

void tabi::logger::TabiLog(ELogLevel a_LogLevel, const char* a_Message, ...)
{
    const auto logger = LoggerRegistry::GetTabiLoggerRegistry().GetDefaultLogger();
    assert(logger && "No default logger has been set!");

    va_list args;
    va_start(args, a_Message);
    logger->Log(a_LogLevel, a_Message, args);
    va_end(args);
}
