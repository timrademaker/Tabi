#pragma once

#include <chrono>
#include <TabiTypes.h>

namespace tabi
{
    namespace stopwatch_detail
    {
        template<typename T>
        constexpr bool is_duration_v = std::chrono::_Is_duration_v<T>;
    }
    
    class Stopwatch
    {
        using clock_t = std::chrono::high_resolution_clock;

    public:
        using nanoseconds = std::chrono::nanoseconds;
        using microseconds = std::chrono::microseconds;
        using milliseconds = std::chrono::milliseconds;
        using seconds = std::chrono::seconds;
        using minutes = std::chrono::minutes;
        using hours = std::chrono::hours;

    public:
        Stopwatch(bool a_StartRunning = true);
        ~Stopwatch() = default;

        /**
         * @brief Start the stopwatch if it's not running
         */
        void Start();
        /**
         * @brief Stop the stopwatch if it's running
         */
        void Stop();
        /**
         * @brief Reset the stopwatch. If the stopwatch was running, it will continue to do so
         */
        void Reset();

        /**
         * @brief Get the time since the stopwatch started in the specified accuracy without stopping it
         * @returns The time since the stopwatch started if it has not been stopped yet. If it has been stopped, this returns the time the stopwatch has been running
         */
        template<typename Accuracy, class = std::enable_if<tabi::stopwatch_detail::is_duration_v<Accuracy>>::type>
        auto GetElapsedTime();

        /**
         * @brief Get the time the stopwatch has recorded in the specified accuracy
         * @returns The time the stopwatch has been running from starting until the last time it was stopped
         */
        template<typename Accuracy, class = std::enable_if<tabi::stopwatch_detail::is_duration_v<Accuracy>>::type>
        auto GetRecordedTime();

    private:
        /**
         * @brief Get the current time
         * @returns The current time
         */
        clock_t::time_point Now();
        
        /**
         * @brief Calculate the difference between two points in time
         * @params a_Start The starting point
         * @params a_End The ending point
         * @returns The difference between a_Start and a_End in the specified accuracy
         */
        template<typename Accuracy>
        auto Duration(clock_t::time_point a_Start, clock_t::time_point a_End);
        /**
         * @brief Get the duration in a specified accuracy
         * @params a_TimeDifference The duration to convert
         * @returns The duration the specified accuracy
         */
        template<typename Accuracy>
        auto Duration(nanoseconds a_TimeDifference);

    private:
        bool m_IsRunning;

        clock_t::time_point m_Start;
        clock_t::time_point m_Stop;

        /// The time this stopwatch has been running for so far, excluding time for which it was stopped
        nanoseconds m_AccumulatedTime;
    };

    template<typename Accuracy, class _Enabled>
    inline auto Stopwatch::GetElapsedTime()
    {
        if (m_IsRunning)
        {
            return Duration<Accuracy>(Now() - m_Start);
        }
        else
        {
            return GetRecordedTime<Accuracy>();
        }
    }

    template<typename Accuracy, class _Enabled>
    inline auto Stopwatch::GetRecordedTime()
    {
        return Duration<Accuracy>(m_AccumulatedTime);
    }

    inline Stopwatch::clock_t::time_point Stopwatch::Now()
    {
        return clock_t::now();
    }

    template<typename Accuracy>
    inline auto Stopwatch::Duration(clock_t::time_point a_Start, clock_t::time_point a_End)
    {
        return Duration<Accuracy>(a_End - a_Start);
    }

    template<typename Accuracy>
    inline auto Stopwatch::Duration(Stopwatch::nanoseconds a_TimeDifference)
    {
        return std::chrono::duration_cast<Accuracy>(a_TimeDifference).count();
    }
}