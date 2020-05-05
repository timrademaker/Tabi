#pragma once

#include "TabiLogger.h"
#include "LoggerRegistry.h"

#include <TabiTypes.h>

#include <string>

namespace tabi
{
    namespace logger
    {
        /** Factory function to create a new logger with one sink.
        * @returns a pointer to the newly created logger
        */
        template<typename Sink, typename ... SinkArgs>
        LoggerPtr CreateLogger(tabi::string a_LoggerName, SinkArgs&& ... a_SinkArgs)
        {
            auto sink = new Sink(tabi::forward<SinkArgs>(a_SinkArgs)...);
            auto l = tabi::make_shared<Logger>(std::move(a_LoggerName), sink);
            LoggerRegistry::GetClientLoggerRegistry().InitializeLogger(l);
            
            return l;
        }

        /** Set the default logger used by the client
        */
        void SetDefaultLogger(LoggerPtr a_Logger);
        /** Log a message to the default logger
        */
        void Log(ELogLevel a_LogLevel, Logger::LogMessage_t a_Message);
        
        /** Factory function to create a new logger with one sink.
        * Not intended for use outside of engine code
        * @returns a pointer to the newly created logger
        */
        template<typename Sink, typename ... SinkArgs>
        LoggerPtr CreateTabiLogger(tabi::string a_LoggerName, SinkArgs&& ... a_SinkArgs)
        {
            auto sink = tabi::make_shared<Sink>(tabi::forward<SinkArgs>(a_SinkArgs)...);
            auto l = tabi::make_shared<Logger>(a_LoggerName, sink);
            LoggerRegistry::GetTabiLoggerRegistry().InitializeLogger(l);

            return l;
        }

        /** Set the default logger used by the engine
        * Should only be called in Application, before the game loop starts.
        */
        void SetDefaultTabiLogger(LoggerPtr a_Logger);
        /** Log a message to the engine's default logger
        */
        void TabiLog(ELogLevel a_LogLevel, Logger::LogMessage_t a_Message);
    }
}