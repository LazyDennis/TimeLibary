#ifndef _TIMECOUNT_HPP
#define _TIMECOUNT_HPP
#include "TimeLibary.hpp"

namespace TimeLibary
{
    class TimeCount
    {
    protected:
        DTime starttime_;
        DTime pausetime_;
        DTime nowtime_;

    private:
        bool running_;
        bool paused_;
        bool stopped_;

    public:
        TimeCount(const DTime &_start = DTime()) noexcept
            : running_(false), paused_(false), stopped_(true), pausetime_(_start), nowtime_(_start) {}
        virtual ~TimeCount() noexcept {}

        virtual void Start() noexcept
        {
            if (!running_)
            {
                starttime_ = DTime::now();
                paused_ = stopped_ = false;
                running_ = true;
            }
            return;
        }
        virtual void Pause() noexcept
        {
            if (running_)
            {
                if (pausetime_ == nowtime_)
                    Now();
                pausetime_ = nowtime_;
                running_ = false;
                paused_ = !stopped_;
            }
            return;
        }
        virtual void Stop() noexcept
        {
            running_ = paused_ = false;
            stopped_ = true;
            return;
        }
        virtual void Reset() noexcept
        {
            Stop();
            starttime_ = pausetime_ = nowtime_ = 0.0;
            return;
        }

        bool Running() const noexcept { return running_; }
        bool Stopped() const noexcept { return stopped_; }
        bool Paused() const noexcept { return paused_; }

        virtual const DTime &Now() noexcept = 0;
    };   
} //TimeLibary

#endif //_TIMECOUNT_HPP
