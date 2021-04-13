#include "MockSink.h"
#include "LogFunctions.h"

#include "TabiLogger.h"
#include "Logging.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(LoggerTests, LogLevelFitering)
{
    // Set up
    tabi::shared_ptr<MockSink> sink = tabi::make_shared<MockSink>();
    tabi::logger::Logger logger("TestLogger", sink);
    logger.SetLogLevel(tabi::logger::ELogLevel::Trace);
    
    // No filtering
    {
        // Set expectations
        EXPECT_CALL(*sink, SinkMessage(::testing::_)).Times(6);

        // Execute
        testlog::LogToAllLevels(&logger, "Test log");
    }

    // Trace filtered
    {
        logger.SetLogLevel(tabi::logger::ELogLevel::Debug);

        // Set expectations
        EXPECT_CALL(*sink, SinkMessage(::testing::_)).Times(5);

        // Execute
        testlog::LogToAllLevels(&logger, "Test log");
    }

    // Trace, Debug filtered
    {
        logger.SetLogLevel(tabi::logger::ELogLevel::Info);

        // Set expectations
        EXPECT_CALL(*sink, SinkMessage(::testing::_)).Times(4);

        // Execute
        testlog::LogToAllLevels(&logger, "Test log");
    }

    // Trace, Debug, Info filtered
    {
        logger.SetLogLevel(tabi::logger::ELogLevel::Warning);

        // Set expectations
        EXPECT_CALL(*sink, SinkMessage(::testing::_)).Times(3);

        // Execute
        testlog::LogToAllLevels(&logger, "Test log");
    }

    // Trace, Debug, Info, Warning filtered
    {
        logger.SetLogLevel(tabi::logger::ELogLevel::Error);

        // Set expectations
        EXPECT_CALL(*sink, SinkMessage(::testing::_)).Times(2);

        // Execute
        testlog::LogToAllLevels(&logger, "Test log");
    }
    
    // Trace, Debug, Info, Warning, Error filtered
    {
        logger.SetLogLevel(tabi::logger::ELogLevel::Critical);

        // Set expectations
        EXPECT_CALL(*sink, SinkMessage(::testing::_)).Times(1);

        // Execute
        testlog::LogToAllLevels(&logger, "Test log");
    }
}

TEST(LoggerTests, LogFlush)
{
    // Set up
    tabi::shared_ptr<MockSink> sink = tabi::make_shared<MockSink>();
    tabi::logger::Logger logger("TestLogger", sink);
    logger.SetLogLevel(tabi::logger::ELogLevel::Trace);

    // Flush on Critical
    {
        logger.FlushOn(tabi::logger::ELogLevel::Critical);

        // Set expectations
        EXPECT_CALL(*sink, Flush()).Times(2);

        // Execute
        testlog::LogToAllLevels(&logger, "Logger flush test");
        testlog::LogToAllLevels(&logger, "Logger flush test");
    }

    // Flush on Error
    {
        logger.FlushOn(tabi::logger::ELogLevel::Error);

        // Set expectations
        EXPECT_CALL(*sink, Flush()).Times(1);

        // Execute
        logger.Log(tabi::logger::ELogLevel::Info, "Logger flush test");     // This call should not trigger flushing
        logger.Log(tabi::logger::ELogLevel::Error, "Logger flush test");
    }
}

TEST(LoggerTests, DefaultLogger)
{
    // Logger for users
    {
        // Set up
        tabi::shared_ptr<MockSink> sink = tabi::make_shared<MockSink>();
        tabi::shared_ptr<tabi::logger::Logger> logger = tabi::make_shared<tabi::logger::Logger>("TestLogger", sink);
        logger->SetLogLevel(tabi::logger::ELogLevel::Trace);
        tabi::logger::SetDefaultLogger(logger);

        // Set expectations
        EXPECT_CALL(*sink, SinkMessage(::testing::_)).Times(3);

        // Execute
        tabi::logger::Log(tabi::logger::ELogLevel::Critical, "Default logger test");
        tabi::logger::Log(tabi::logger::ELogLevel::Critical, "Default logger test");
        tabi::logger::Log(tabi::logger::ELogLevel::Critical, "Default logger test");
    }

    // Tabi logger
    {
        // Set up
        tabi::shared_ptr<MockSink> sink = tabi::make_shared<MockSink>();
        tabi::shared_ptr<tabi::logger::Logger> logger = tabi::make_shared<tabi::logger::Logger>("TabiTestLogger", sink);
        logger->SetLogLevel(tabi::logger::ELogLevel::Trace);
        tabi::logger::SetDefaultTabiLogger(logger);

        // Set expectations
        EXPECT_CALL(*sink, SinkMessage(::testing::_)).Times(3);

        // Execute
        tabi::logger::TabiLog(tabi::logger::ELogLevel::Critical, "Default Tabi logger test");
        tabi::logger::TabiLog(tabi::logger::ELogLevel::Critical, "Default Tabi logger test");
        tabi::logger::TabiLog(tabi::logger::ELogLevel::Critical, "Default Tabi logger test");
    }
}

TEST(LoggerTests, DoubleSink)
{
    // Set up
    tabi::shared_ptr<MockSink> sink = tabi::make_shared<MockSink>();
    tabi::shared_ptr<MockSink> sink2 = tabi::make_shared<MockSink>();
    tabi::logger::Logger logger("TestLogger", sink);
    logger.AddSink(sink2);
    logger.SetLogLevel(tabi::logger::ELogLevel::Trace);

    // Set expectations
    EXPECT_CALL(*sink, SinkMessage(::testing::_)).Times(1);
    EXPECT_CALL(*sink2, SinkMessage(::testing::_)).Times(1);

    // Execute
    logger.Log(tabi::logger::ELogLevel::Critical, "Test");
}

TEST(LoggerTests, SinkUsedInTwoLoggers)
{
    // Set up
    tabi::shared_ptr<MockSink> sink = tabi::make_shared<MockSink>();
    tabi::logger::Logger logger("TestLogger", sink);
    tabi::logger::Logger logger2("TestLogger2", sink);
    logger.SetLogLevel(tabi::logger::ELogLevel::Trace);
    logger2.SetLogLevel(tabi::logger::ELogLevel::Trace);

    // Set expectations
    EXPECT_CALL(*sink, SinkMessage(::testing::_)).Times(2);

    // Execute
    logger.Log(tabi::logger::ELogLevel::Critical, "Test");
    logger2.Log(tabi::logger::ELogLevel::Critical, "Test");
}
