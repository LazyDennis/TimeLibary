#ifndef _STOPWATCH_HPP
#define _STOPWATCH_HPP
#include "TimeCount.hpp"
#include <vector>

namespace TimeLibary
{
    using std::vector;

    class stopwatch : public TimeCount
    {
    public:
        struct laptime
        {
            const unsigned int index;
            const BasicTime lap_t;
            const BasicTime sum_t;
            laptime(int i = 0, BasicTime l_t = BasicTime(), BasicTime s_t = BasicTime()) : index(i >= 0 ? i : -i), lap_t(l_t), sum_t(s_t) {}
            ~laptime() {}
            //friend std::ostream &operator<<(std::ostream os, laptime &lt) noexcept;
        };

    private:
        vector<laptime> lap_time;

    public:
        stopwatch(const BasicTime &s_t = BasicTime()) noexcept : TimeCount(s_t) { lap_time.push_back(laptime()); }
        ~stopwatch() noexcept {}
        virtual void stop() noexcept;
        virtual void reset() noexcept { stop(); }
        virtual const BasicTime &now() noexcept;

        void lap() noexcept;
        const laptime &getlaptime(int index) const noexcept;
    };

    void stopwatch::stop() noexcept
    {
        TimeCount::stop();
        start_time = pause_time = now_time = 0;
        lap_time.clear();
    }

    const BasicTime &stopwatch::now() noexcept
    {
        if (is_running())
        {
            now_time = BasicTime::now() - start_time + pause_time;
        }
        return now_time;
    }

    void stopwatch::lap() noexcept
    {
        if (is_running())
        {
            lap_time.push_back(laptime(lap_time.size(), now_time - lap_time[lap_time.size() - 1].sum_t, now_time));
        }
        return;
    }

    const stopwatch::laptime &stopwatch::getlaptime(int index) const noexcept
    {
        index = index >= 0 ? index : -index;
        if (index < lap_time.size())
            return lap_time[index];
        else
            return *(lap_time.cend() - 1);
    }

    /*std::ostream &operator<<(std::ostream &os, const stopwatch::laptime &lt) noexcept
    {
        os << lt.index << "\t" << lt.lap_t << "\t" << lt.sum_t;
        return os;
    }*/
} // TimeLibary

#endif //_STOPWATCH_HPP