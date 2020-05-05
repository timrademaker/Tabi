#pragma once

#include "ISink.h"

#include <TabiTypes.h>

namespace tabi
{
    namespace logger
    {
        class ConsoleSink : public ISink
        {
        public:
            ConsoleSink();
            virtual ~ConsoleSink() = default;

            virtual void SinkMessage(const SinkMsg_t& a_Message) override final;
            virtual void Flush() override final;

        private:
            tabi::unique_ptr<spdlog::sinks::sink> m_Sink;
        };
    }
}