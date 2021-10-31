#ifndef _TIMER_HPP
#define _TIMER_HPP
#include "TimeCount.hpp"

namespace TimeLibary
{
    class Timer : public TimeCount
    {
    private:
        BasicTime set_time;

    public:
        Timer(const BasicTime &s_t = BasicTime()) noexcept : set_time(s_t), TimeCount(s_t) {}
        virtual ~Timer() noexcept {}
        virtual void stop() noexcept
        {
            TimeCount::stop();
            now_time = pause_time = set_time;
            return;
        }
        virtual void reset() noexcept
        {
            TimeCount::reset();
            set_time = 0;
            return;
        }
        virtual const BasicTime &now() noexcept
        {
            if (is_running())
            {
                now_time = pause_time - BasicTime::now() + start_time;
                if (now_time <= 0)
                {
                    now_time = 0;
                    TimeCount::stop();
                }
            }
            return now_time;
        }

        void settime(const BasicTime &s_t) noexcept
        {
            set_time = now_time = pause_time = s_t;
        }
    };
} // TimeLibary

#endif // _TIMER_HPP
