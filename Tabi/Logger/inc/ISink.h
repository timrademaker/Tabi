#pragma once

#include <spdlog/sinks/base_sink.h>

#include <string>

namespace tabi
{
    namespace logger
    {
        /** The base sink class
        */
        class ISink : public spdlog::sinks::base_sink<spdlog::details::null_mutex>
        {
        public:
            using SinkMsg_t = spdlog::details::log_msg;
            using MemoryBuffer_t = spdlog::memory_buf_t;

            virtual ~ISink() = default;

            /** The function that sinks the message to a sink.
            * For example, a file sink would send the messages to a file.
            */
            virtual void SinkMessage(const SinkMsg_t& a_Message) = 0;
            /** Flushes all messages that are supposed to have been sunk.
            * This is mostly useful in multi-threaded applications, where it is not guaranteed that the messages have been sunk at any given time.
            */
            virtual void Flush() = 0;

        protected:
            /** Formats the message.
            * If used, should be used before sinking the message.
            */
            void FormatSinkMessage(const SinkMsg_t a_Message, MemoryBuffer_t& a_FormattedMessage)
            {
                static spdlog::pattern_formatter fm;
                fm.format(a_Message, a_FormattedMessage);
            }

        private:
            void sink_it_(const spdlog::details::log_msg& a_Msg) override final
            {
                SinkMessage(a_Msg);
            }

            void flush_() override final
            {
                Flush();
            }
        };

    }
}