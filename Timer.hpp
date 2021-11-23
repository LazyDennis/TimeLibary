#ifndef _TIMER_HPP
#define _TIMER_HPP
#include "TimeCount.hpp"

namespace TimeLibary
{
    class Timer : public TimeCount
    {
    private:
        DTime settime_;

    public:
        Timer(const DTime &_start = DTime()) noexcept : settime_(_start), TimeCount(_start) {}
        virtual ~Timer() noexcept {}
        virtual void Stop() noexcept
        {
            TimeCount::Stop();
            nowtime_ = pausetime_ = settime_;
            return;
        }
        virtual void Reset() noexcept
        {
            TimeCount::Reset();
            settime_ = 0.0;
            return;
        }
        virtual const DTime &Now() noexcept
        {
            if (Running())
            {
                nowtime_ = pausetime_ - DTime::Now() + starttime_;
                if (nowtime_ <= 0.0)
                {
                    nowtime_ = 0.0;
                    TimeCount::Stop();
                }
            }
            return nowtime_;
        }

        void settime(const DTime &_start) noexcept
        {
            settime_ = nowtime_ = pausetime_ = _start;
        }
    };
} // TimeLibary

#endif // _TIMER_HPP
