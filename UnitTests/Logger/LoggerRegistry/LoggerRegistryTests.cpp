#include "LoggerRegistry.h"
#include "TabiLogger.h"

#include "gtest/gtest.h"

TEST(LoggerRegistryTests, DefaultLoggerInRegistry)
{
    // Set up
    tabi::shared_ptr<tabi::logger::Logger> logger = tabi::make_shared<tabi::logger::Logger>("TestLogger");

    tabi::logger::LoggerRegistry& loggerRegistry = tabi::logger::LoggerRegistry::GetClientLoggerRegistry();

    loggerRegistry.SetDefaultLogger(logger);

    // Get default logger and compare
    EXPECT_EQ(logger, loggerRegistry.GetDefaultLogger());
}

TEST(LoggerRegistryTests, GetLoggerByName)
{
    // Set up
    tabi::string firstLoggerName("TestLogger");
    tabi::string secondLoggerName("OtherLogger");
    tabi::shared_ptr<tabi::logger::Logger> firstLogger = tabi::make_shared<tabi::logger::Logger>(firstLoggerName);
    tabi::shared_ptr<tabi::logger::Logger> secondLogger = tabi::make_shared<tabi::logger::Logger>(secondLoggerName);

    tabi::logger::LoggerRegistry& loggerRegistry = tabi::logger::LoggerRegistry::GetClientLoggerRegistry();
    loggerRegistry.AddLogger(firstLogger);
    loggerRegistry.AddLogger(secondLogger);

    // Get logger by name and compare
    EXPECT_EQ(firstLogger, loggerRegistry.GetLoggerByName(firstLoggerName));
    EXPECT_EQ(secondLogger, loggerRegistry.GetLoggerByName(secondLoggerName));
}


TEST(LoggerRegistryTests, CreateLoggerWithExistingName)
{
    // Set up
    tabi::string loggerName("TestLogger");
    tabi::shared_ptr<tabi::logger::Logger> firstLogger = tabi::make_shared<tabi::logger::Logger>(loggerName);
    tabi::shared_ptr<tabi::logger::Logger> secondLogger = tabi::make_shared<tabi::logger::Logger>(loggerName);

    tabi::logger::LoggerRegistry& loggerRegistry = tabi::logger::LoggerRegistry::GetClientLoggerRegistry();
    loggerRegistry.AddLogger(firstLogger);
    
    EXPECT_DEATH(loggerRegistry.AddLogger(secondLogger), "");
}
