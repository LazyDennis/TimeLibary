#ifndef _STOPWATCH_HPP
#define _STOPWATCH_HPP
#include <vector>
#include "TimeCount.hpp"

namespace TimeLibary
{
    using std::vector;

    class stopwatch : public TimeCount
    {
    public:
        struct LapTime
        {
            const unsigned int index_;
            const DTime lapt_;
            const DTime sumt_;
            LapTime(int _index = 0, DTime _lapt = DTime(), DTime _start = DTime()) :
                index_(_index >= 0 ? _index : -_index), lapt_(_lapt), sumt_(_start) {}
            ~LapTime() {}
            //friend std::ostream &operator<<(std::ostream os, LapTime &lt) noexcept;
        };

    private:
        vector<LapTime> laptime_;

    public:
        stopwatch(const DTime &start = DTime()) noexcept : TimeCount(start) { laptime_.push_back(LapTime()); }
        ~stopwatch() noexcept {}
        virtual void Stop() noexcept;
        virtual void Reset() noexcept { Stop(); }
        virtual const DTime &Now() noexcept;

        void Lap() noexcept;
        const LapTime &getLapTime(int index_) const noexcept;
    };

    void stopwatch::Stop() noexcept
    {
        TimeCount::Stop();
        starttime_ = pausetime_ = nowtime_ = 0.0;
        laptime_.clear();
    }

    const DTime &stopwatch::Now() noexcept
    {
        if (Running())
        {
            nowtime_ = DTime::now() - starttime_ + pausetime_;
        }
        return nowtime_;
    }

    void stopwatch::Lap() noexcept
    {
        if (Running())
        {
            laptime_.push_back(LapTime(laptime_.size(), nowtime_ - laptime_[laptime_.size() - 1].sumt_, nowtime_));
        }
        return;
    }

    const stopwatch::LapTime &stopwatch::getLapTime(int index_) const noexcept
    {
        index_ = index_ >= 0 ? index_ : -index_;
        if (index_ < laptime_.size())
            return laptime_[index_];
        else
            return *(laptime_.cend() - 1);
    }

    /*std::ostream &operator<<(std::ostream &os, const stopwatch::LapTime &lt) noexcept
    {
        os << lt.index_ << "\t" << lt.lapt_ << "\t" << lt.sumt_;
        return os;
    }*/
} // TimeLibary

#endif //_STOPWATCH_HPP