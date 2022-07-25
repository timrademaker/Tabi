#pragma once

#include "TabiLogger.h"
#include "LoggerRegistry.h"

#include <TabiTypes.h>
#include <TabiMacros.h>

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
            auto sink = tabi::make_shared<Sink>(tabi::forward<SinkArgs>(a_SinkArgs)...);
            auto l = tabi::make_shared<Logger>(std::move(a_LoggerName), std::move(sink));
            LoggerRegistry::GetClientLoggerRegistry().InitializeLogger(l);
            
            return l;
        }

        /** Set the default logger used by the client
        */
        void SetDefaultLogger(LoggerPtr a_Logger);
        /** Log a message to the default logger
        */
        void Log(ELogLevel a_LogLevel, const char* a_Message, ...);
        
        /** Factory function to create a new logger with one sink.
        * Not intended for use outside of engine code
        * @returns a pointer to the newly created logger
        */
        template<typename Sink, typename ... SinkArgs>
        LoggerPtr CreateTabiLogger(tabi::string a_LoggerName, SinkArgs&& ... a_SinkArgs)
        {
            auto sink = tabi::make_shared<Sink>(tabi::forward<SinkArgs>(a_SinkArgs)...);
            auto l = tabi::make_shared<Logger>(std::move(a_LoggerName), std::move(sink));
            LoggerRegistry::GetTabiLoggerRegistry().InitializeLogger(l);

            return l;
        }

        /** Set the default logger used by the engine
        * Should only be called in Application, before the game loop starts.
        */
        void SetDefaultTabiLogger(LoggerPtr a_Logger);
        /** Log a message to the engine's default logger
        */
        void TabiLog(ELogLevel a_LogLevel, const char* a_Message, ...);
    }

#define TABI_TRACE(message, ...) ::tabi::logger::TabiLog(::tabi::logger::ELogLevel::Trace, message, __VA_ARGS__)
#define TABI_DEBUG(message, ...) ::tabi::logger::TabiLog(::tabi::logger::ELogLevel::Debug, message, __VA_ARGS__)
#define TABI_INFO(message, ...) ::tabi::logger::TabiLog(::tabi::logger::ELogLevel::Info, message, __VA_ARGS__)
#define TABI_WARN(message, ...) ::tabi::logger::TabiLog(::tabi::logger::ELogLevel::Warning, message, __VA_ARGS__)
#define TABI_ERROR(message, ...) ::tabi::logger::TabiLog(::tabi::logger::ELogLevel::Error, message, __VA_ARGS__)
#define TABI_CRITICAL(message, ...) ::tabi::logger::TabiLog(::tabi::logger::ELogLevel::Critical, message, __VA_ARGS__)
}
