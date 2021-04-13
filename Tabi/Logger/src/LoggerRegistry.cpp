#include "LoggerRegistry.h"

#include "TabiLogger.h"
#include "ConsoleSink.h"


using namespace tabi::logger;

LoggerRegistry& LoggerRegistry::GetClientLoggerRegistry()
{    
    static LoggerRegistry s_ClientLoggerRegistry;
    return s_ClientLoggerRegistry;
}

LoggerRegistry& LoggerRegistry::GetTabiLoggerRegistry()
{
    static LoggerRegistry s_TabiLoggerRegistry;
    return s_TabiLoggerRegistry;
}

void LoggerRegistry::InitializeLogger(LoggerPtr a_Logger, bool a_ShouldRegister)
{
    a_Logger->SetLogLevel(ELogLevel::Trace);
    a_Logger->FlushOn(ELogLevel::Critical);
    
    if (a_ShouldRegister)
    {
        AddLogger(std::move(a_Logger));
    }
}

void LoggerRegistry::AddLogger(LoggerPtr a_Logger)
{
    if (m_Loggers.find(a_Logger->GetName()) != m_Loggers.end())
    {
        printf("\nLogger with name %s already exists!", a_Logger->GetName().c_str());
        assert(false);
    }

    m_Loggers[a_Logger->GetName()] = std::move(a_Logger);
}

void LoggerRegistry::SetDefaultLogger(LoggerPtr a_Logger)
{
    m_DefaultLogger = std::move(a_Logger);
}

LoggerPtr LoggerRegistry::GetLoggerByName(LoggerName_t a_LoggerName)
{
    auto iter = m_Loggers.find(a_LoggerName);
    if (iter != m_Loggers.end())
    {
        return iter->second;
    }

    return nullptr;
}

LoggerRegistry::LoggerRegistry()
{
    constexpr const char* defaultLoggerName = "";
    auto sink = tabi::make_shared<ConsoleSink>();

    m_DefaultLogger = std::make_shared<Logger>(defaultLoggerName, sink);
    InitializeLogger(m_DefaultLogger, false);
    m_Loggers[defaultLoggerName] = m_DefaultLogger;

}
