#pragma once

#include <Logging.h>

namespace tabi
{
    namespace renderer
    {
        extern tabi::logger::LoggerPtr s_GraphicsLogger;
    }
}

#define LOG_INFO(message, ...) ::tabi::renderer::s_GraphicsLogger->Log(::tabi::logger::ELogLevel::Info, message, __VA_ARGS__)
#define LOG_WARNING(message, ...) ::tabi::renderer::s_GraphicsLogger->Log(::tabi::logger::ELogLevel::Warning, message, __VA_ARGS__)
#define LOG_ERROR(message, ...) ::tabi::renderer::s_GraphicsLogger->Log(::tabi::logger::ELogLevel::Error, message, __VA_ARGS__)
