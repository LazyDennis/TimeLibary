#ifndef _TIMECOUNT_HPP
#define _TIMECOUNT_HPP
#include "TimeLibary.hpp"

namespace TimeLibary
{
    class TimeCount
    {
    protected:
        BasicTime start_time;
        BasicTime pause_time;
        BasicTime now_time;

    private:
        bool running;
        bool paused;
        bool stopped;

    public:
        TimeCount(const BasicTime &s_t = BasicTime()) noexcept
            : running(false), paused(false), stopped(true), pause_time(s_t), now_time(s_t) {}
        virtual ~TimeCount() noexcept {}

        virtual void start() noexcept
        {
            if (!running)
            {
                start_time = BasicTime::now();
                paused = stopped = false;
                running = true;
            }
            return;
        }
        virtual void pause() noexcept
        {
            if (running)
            {
                if (pause_time == now_time)
                    now();
                pause_time = now_time;
                running = false;
                paused = !stopped;
            }
            return;
        }
        virtual void stop() noexcept
        {
            running = paused = false;
            stopped = true;
            return;
        }
        virtual void reset() noexcept
        {
            stop();
            start_time = pause_time = now_time = 0;
            return;
        }

        bool is_running() const noexcept { return running; }
        bool is_stopped() const noexcept { return stopped; }
        bool is_paused() const noexcept { return paused; }

        virtual const BasicTime &now() noexcept = 0;
    };   
} //TimeLibary

#endif //_TIMECOUNT_HPP
