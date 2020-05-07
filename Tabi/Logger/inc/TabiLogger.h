#pragma once

#include "ISink.h"

#include <TabiMacros.h>
#include <TabiTypes.h>

#include <spdlog/logger.h>


namespace tabi
{
    namespace logger
    {
        class Logger;
        using LoggerPtr = tabi::shared_ptr<Logger>;

        /** Enum containing the different levels of severity for a logged message
        */
        enum class TABI_EXPORT ELogLevel
        {
            Trace       = spdlog::level::trace,
            Debug       = spdlog::level::debug,
            Info        = spdlog::level::info,
            Warning     = spdlog::level::warn,
            Error       = spdlog::level::err,
            Critical    = spdlog::level::critical
        };

        /** The Logger class
        */
        class TABI_EXPORT Logger
        {
            using SinkPtr = ISink*;
            using InternalLogLevel_t = spdlog::level::level_enum;
        public:
            using LogMessage_t = tabi::string;

            /** Constructor to create a logger without sink
            * @params a_LoggerName: The name of the logger.
            */
            Logger(const tabi::string a_LoggerName);
            /** Constructor to create a logger with one sink
            * @params a_LoggerName: The name of the logger.
            * @params a_Sink: A pointer to the sink this logger should use
            */
            Logger(const tabi::string a_LoggerName, SinkPtr a_Sink);

            /**
            * @returns the name of the logger
            */
            tabi::string GetName() { return tabi::string(m_Logger->name().c_str()); }

            /** Adds a sink to the logger, allowing the logger to use multiple sinks.
            */
            void AddSink(SinkPtr a_Sink);
            /** Specifies the minimum log level needed before sinking a message.
            */
            void SetLogLevel(ELogLevel a_LogLevel);
            /** Specifies the log level on which the logger should flush all of its sinks.
            */
            void FlushOn(ELogLevel a_LogLevel);
            /** Logs a message to all sinks (if the log level is high enough).
            */
            void Log(ELogLevel a_LogLevel, LogMessage_t a_LogMessage);

        private:
            /** Used to translate ELogLevel to the log level used by the library the logger uses internally
            */
             InternalLogLevel_t TranslateLogLevel(const ELogLevel a_LogLevel);

        private:
            ELogLevel m_LogLevel = ELogLevel::Trace;
            ELogLevel m_FlushOn = ELogLevel::Critical;

            tabi::shared_ptr<spdlog::logger> m_Logger;
            tabi::vector<SinkPtr> m_Sinks;
        };
    }
}