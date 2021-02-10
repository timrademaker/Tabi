#include "LogFunctions.h"

#include "TabiLogger.h"

void testlog::LogToAllLevels(::tabi::logger::Logger* logger, const tabi::string& a_Message)
{
    logger->Log(tabi::logger::ELogLevel::Trace, a_Message);
    logger->Log(tabi::logger::ELogLevel::Debug, a_Message);
    logger->Log(tabi::logger::ELogLevel::Info, a_Message);
    logger->Log(tabi::logger::ELogLevel::Warning, a_Message);
    logger->Log(tabi::logger::ELogLevel::Error, a_Message);
    logger->Log(tabi::logger::ELogLevel::Critical, a_Message);
}
