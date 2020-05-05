#pragma once

#include <TabiTypes.h>

#include <string>
#include <unordered_map>
#include <memory>


namespace tabi
{
    namespace logger
    {
        class Logger;
        using LoggerPtr = tabi::shared_ptr<Logger>;

        /** A registry holding all created loggers.
        * There are two instances: One for the client (Game), and one for the engine (Tabi)
        */
        class LoggerRegistry
        {
            using LoggerName_t = tabi::string;
        public:
            /**
            * @returns the client's logger registry
            */
            static LoggerRegistry& GetClientLoggerRegistry();
            /**
            * This function is only intended to be called from the engine, and not by the game.
            @retuns the engine's logger registry
            */
            static LoggerRegistry& GetTabiLoggerRegistry();

            /** Initializes a logger
            * @params a_Logger: The logger to initialize.
            * @params a_ShouldRegister: Whether the logger should be stored in the registry or not. Defaults to true.
            */
            void InitializeLogger(LoggerPtr a_Logger, bool a_ShouldRegister = true);
            /** Adds a logger to the registry.
            * @params a_Logger: The logger to add to the registry.
            */
            void AddLogger(LoggerPtr a_Logger);
            /** Sets the registry's default logger.
            * @params a_Logger: The logger to use as default logger
            */
            void SetDefaultLogger(LoggerPtr a_Logger);

            /**
            * @returns the default logger.
            */
            inline LoggerPtr GetDefaultLogger() { return m_DefaultLogger; };
            /**
            * @returns the logger with the specified name (nullptr if not found).
            */
            LoggerPtr GetLoggerByName(LoggerName_t a_LoggerName);

        private:
            LoggerRegistry();
            LoggerRegistry(const LoggerRegistry&) = delete;
            void operator=(const LoggerRegistry&) = delete;

        private:
            tabi::unordered_map<LoggerName_t, LoggerPtr> m_Loggers;
            LoggerPtr m_DefaultLogger;
        };
    }
}