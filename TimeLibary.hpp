#pragma once
#ifndef _TIMELIB_HPP
#define _TIMELIB_HPP
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <chrono>
#include <ctime>
#include <string>
#include <filesystem>
#include <DUtilLib.hpp>

constexpr auto DTIMEVERSION = "0.1.0";
#define TIMESPECTOD(x) (x.tv_sec + x.tv_nsec / DTimeType(1e9))

namespace TimeLibary
{
    using std::time_t;
    using std::timespec;

    class DTime;

    template <class CharT>
    std::basic_string<CharT> inttostr(long long _num) noexcept;
    template <>
    std::basic_string<char> inttostr(long long _num) noexcept;
    template <>
    std::basic_string<wchar_t> inttostr(long long _num) noexcept;

    class DTime
    {
    public:
        typedef double DTimeType;
        enum DTimeArea { Duration, Local };

    private:
        DTimeType time_;

    public:
        DTime() noexcept : time_(DTimeType(0)) {}
        DTime(const DTime &_other) noexcept : time_(_other.time_) {}
        DTime(DTime &&_other) noexcept : time_(_other.time_) {}
        DTime(DTimeType _time) noexcept : time_(_time) {}
        explicit DTime(time_t _ctime) noexcept : time_((DTimeType)_ctime) {}
        explicit DTime(const timespec &_timespec) noexcept :
            time_(TIMESPECTOD(_timespec)) {}

        ~DTime() = default;

        const DTime &operator=(const DTime &_other) noexcept
        {
            time_ = _other.time_;
            return *this;
        }
        /*const DTime &operator=(DTime &&_other) noexcept
        {
            time_ = _other.time_;
            return *this;
        }*/
        const DTime &operator=(DTimeType _time) noexcept
        {
            time_ = _time;
            return *this;
        }
        const DTime &operator=(time_t _ctime) noexcept
        {
            time_ = (DTimeType)_ctime;
            return *this;
        }
        const DTime &operator=(const timespec &_timespec) noexcept
        {
            time_ = TIMESPECTOD(_timespec);
            return *this;
        }

        explicit operator time_t() noexcept { return time_t(time_); }
        explicit operator DTimeType() noexcept { return time_; }
        explicit operator timespec() noexcept
        {
            return timespec{time_t(time_), long((time_ - time_t(time_)) * 1e9)};
        }


        DTime operator+(const DTime &_other) const noexcept
        {
            return DTime(time_ + _other.time_);
        }
        DTime operator+(DTimeType _time) const noexcept
        {
            return DTime(time_ + _time);
        }
        DTime operator+(time_t _ctime) const noexcept
        {
            return DTime(time_ + _ctime);
        }
        DTime operator+(const timespec &_timespec) const noexcept
        {
            return *this + DTime(_timespec);
        }

        DTime operator-(const DTime &_other) const noexcept
        {
            return DTime(time_ - _other.time_);
        }
        DTime operator-(DTimeType _time)
        {
            return DTime(time_ - _time);
        }
        DTime operator-(time_t _ctime) const noexcept
        {
            return DTime(time_ - _ctime);
        }
        DTime operator-(const timespec &_timespec) const noexcept
        {
            return *this - DTime(_timespec);
        }

        DTime operator*(long _times) const noexcept
        {
            return DTime(time_ * _times);
        }
        DTime operator/(long _divisor) const noexcept
        {
            if (_divisor)
            {
                return DTime(time_ / _divisor);
            }
            else
            {
                return DTime((DTimeType)(size_t(-1)));
            }

        }

        const DTime &operator+=(const DTime &_other) noexcept
        {
            *this = *this + _other;
            return *this;
        }
        const DTime &operator+=(DTimeType _time) noexcept
        {
            time_ += _time;
            return *this;
        }
        const DTime &operator+=(time_t _ctime) noexcept
        {
            time_ += _ctime;
            return *this;
        }
        const DTime &operator+=(const timespec &_timespec) noexcept
        {
            *this = *this + _timespec;
            return *this;
        }

        const DTime &operator-=(const DTime &_other) noexcept
        {
            *this = *this - _other;
            return *this;
        }
        const DTime &operator-=(DTimeType _time) noexcept
        {
            time_ -= _time;
            return *this;
        }
        const DTime &operator-=(time_t _ctime) noexcept
        {
            time_ -= _ctime;
            return *this;
        }
        const DTime &operator-=(const timespec &_timespec) noexcept
        {
            *this = *this - _timespec;
            return *this;
        }

        const DTime &operator*=(long _times) noexcept
        {
            *this = *this * _times;
            return *this;
        }
        const DTime &operator/=(long _divisor) noexcept
        {
            *this = *this / _divisor;
            return *this;
        }

        bool operator<(const DTime &_other) const noexcept
        {
            return time_ < _other.time_;
        }
        bool operator<(DTimeType _time) const noexcept
        {
            return time_ < _time;
        }
        bool operator<(time_t _ctime) const noexcept
        {
            return time_ < DTimeType(_ctime);
        }
        bool operator<(const timespec &_timespec) const noexcept
        {
            return time_ < TIMESPECTOD(_timespec);
        }

        bool operator>(const DTime &_other) const noexcept
        {
            return time_ > _other.time_;
        }
        bool operator>(DTimeType _time) const noexcept
        {
            return time_ > _time;
        }
        bool operator>(time_t _ctime) const noexcept
        {
            return time_ > DTimeType(_ctime);
        }
        bool operator>(const timespec &_timespec) const noexcept
        {
            return time_ > TIMESPECTOD(_timespec);
        }

        bool operator==(const DTime &_other) const noexcept
        {
            return time_ == _other.time_;
        }
        bool operator==(DTimeType _time) const noexcept
        {
            return time_ == _time;
        }
        bool operator==(time_t _ctime) const noexcept
        {
            return time_ == DTimeType(_ctime);
        }
        bool operator==(const timespec &_timespec) const noexcept
        {
            return time_ == TIMESPECTOD(_timespec);
        }

        bool operator!=(const DTime &_other) const noexcept
        {
            return time_ != _other.time_;
        }
        bool operator!=(DTimeType _time) const noexcept
        {
            return time_ != _time;
        }
        bool operator!=(time_t _ctime) const noexcept
        {
            return time_ != DTimeType(_ctime);
        }
        bool operator!=(const timespec &_timespec) const noexcept
        {
            return time_ != TIMESPECTOD(_timespec);
        }

        bool operator<=(const DTime &_other) const noexcept
        {
            return time_ <= _other.time_;
        }
        bool operator<=(DTimeType _time) const noexcept
        {
            return time_ <= _time;
        }
        bool operator<=(time_t _ctime) const noexcept
        {
            return time_ <= DTimeType(_ctime);
        }
        bool operator<=(const timespec &_timespec) const noexcept
        {
            return time_ <= TIMESPECTOD(_timespec);
        }

        bool operator>=(const DTime &_other) const noexcept
        {
            return time_ >= _other.time_;
        }
        bool operator>=(DTimeType _time) const noexcept
        {
            return time_ >= _time;
        }
        bool operator>=(time_t _ctime) const noexcept
        {
            return time_ >= DTimeType(_ctime);
        }
        bool operator>=(const timespec &_timespec) const noexcept
        {
            return time_ >= TIMESPECTOD(_timespec);
        }

        double Day() const noexcept { return time_ / 3600 / 24; }
        double Hour() const noexcept { return time_ / 3600; }
        double Minute() const noexcept { return time_ / 60; }
        double Second() const noexcept { return time_; }
        double MiliSecond() const noexcept { return time_ * 1e3; }
        double MicroSecond() const noexcept { return time_ * 1e6; }
        double NanoSecond() const noexcept { return time_ * 1e9; }


        std::string ToString(const std::string &_format, DTimeArea _timearea = Duration) const noexcept
        {
            std::tm *TimeStruct;
            std::string timestring(100, '\0');
            time_t temptime = time_t(time_);
            if (_timearea == Local)
                TimeStruct = std::localtime(&temptime);
            else
                TimeStruct = std::gmtime(&temptime);
            std::strftime(timestring.data(), 100, _format.c_str(), TimeStruct);
            return timestring;

        }

        template <class CharT>
        std::basic_string<CharT> string(std::basic_string<CharT> _format, DTimeArea _timearea = Duration) const noexcept
        {
            std::tm TimeStruct;
            time_t temptime = time_t(time_);
            if (_timearea == Local)
                localtime_s(&TimeStruct, &temptime);
            else
                gmtime_s(&TimeStruct, &temptime);
            std::basic_string<CharT> year =
                inttostr<CharT>(TimeStruct.tm_year + 1900);
            std::basic_string<CharT> month =
                inttostr<CharT>(TimeStruct.tm_mon + 1);
            if (month.size() < 2)
                month.insert(month.begin(), (CharT)'0');
            std::basic_string<CharT> day =
                inttostr<CharT>(TimeStruct.tm_mday);
            if (day.size() < 2)
                day.insert(day.begin(), (CharT)'0');
            std::basic_string<CharT> hour =
                inttostr<CharT>(TimeStruct.tm_hour);
            if (hour.size() < 2)
                hour.insert(hour.begin(), (CharT)'0');
            std::basic_string<CharT> min =
                inttostr<CharT>(TimeStruct.tm_min);
            if (min.size() < 2)
                min.insert(min.begin(), (CharT)'0');
            std::basic_string<CharT> sec =
                inttostr<CharT>(TimeStruct.tm_sec);
            if (sec.size() < 2)
                sec.insert(sec.begin(), (CharT)'0');
            std::basic_string<CharT> msec =
                inttostr<CharT>((int)((time_ - (int)time_) * 1e3));
            if (_format == (std::basic_string<CharT>)"YYYY/MM/DD" ||
                _format == (std::basic_string<CharT>)"yyyy/mm/dd")
            {
                return year + (CharT)'/' + month + (CharT)'/' + day;
            }
            else if (_format == (std::basic_string<CharT>)"YY/MM/DD" ||
                _format == (std::basic_string<CharT>)"yy/mm/dd")
            {
                year.erase(year.begin(), year.begin() + 2);
                return year + (CharT)'/' + month + (CharT)'/' + day;
            }
            else if (_format == (std::basic_string<CharT>)"YYYY-MM-DD" ||
                _format == (std::basic_string<CharT>)"yyyy-mm-dd")
            {
                return year + (CharT)'-' + month + (CharT)'-' + day;
            }
            else if (_format == (std::basic_string<CharT>)"YY-MM-DD" ||
                _format == (std::basic_string<CharT>)"yy-mm-dd")
            {
                year.erase(year.begin(), year.begin() + 2);
                return year + (CharT)'-' + month + (CharT)'-' + day;
            }
            else if (_format == (std::basic_string<CharT>)"HH:MM:SS" ||
                _format == (std::basic_string<CharT>)"hh:mm:ss")
            {
                return hour + (CharT)':' + min + (CharT)':' + sec;
            }
            else if (_format == (std::basic_string<CharT>)"HH:MM:SS.XXX" ||
                _format == (std::basic_string<CharT>)"hh:mm:ss.xxx")
            {
                return hour + (CharT)':' + min + (CharT)':' + sec + (CharT)'.' + msec;
            }
            else
                return (std::basic_string<CharT>)"";
        }

        friend DTime operator-(const DTime &_time) noexcept;

        static DTime Now()
        {
            timespec temptimespec;
            auto result = std::timespec_get(&temptimespec, TIME_UTC);
            if (TIME_UTC == result)
                return DTime(temptimespec);
            else
                return DTime(DTimeType(0));
        }

    }; // class DTime

    inline DTime operator-(const DTime &_time) noexcept
    {
        return DTime(-_time.time_);
    }

    inline DTime operator+(DTime::DTimeType _time, const DTime &_dtime) noexcept
    {
        return _dtime + _time;
    }
    inline DTime operator+(time_t _ctime, const DTime &_dtime) noexcept
    {
        return _dtime + _ctime;
    }
    inline DTime operator+(const timespec &_timespec,
        const DTime &_dtime) noexcept
    {
        return _dtime + _timespec;
    }

    inline DTime operator-(DTime::DTimeType _time, const DTime &_dtime) noexcept
    {
        return DTime(_time) - _dtime;
    }
    inline DTime operator-(time_t _ctime, const DTime &_dtime) noexcept
    {
        return DTime(_ctime) - _dtime;
    }
    inline DTime operator-(const timespec &_timespec,
        const DTime &_dtime) noexcept
    {
        return DTime(_timespec) - _dtime;
    }

    inline DTime operator*(long _times, const DTime &_dtime) noexcept
    {
        return _dtime * _times;
    }

    inline DTime::DTimeType operator+=(DTime::DTimeType &_time, const DTime &_dtime)
    {
        _time = DTime::DTimeType(_time + _dtime);
        return _time;
    }

    inline time_t operator+=(time_t &_ctime,
        const DTime &_dtime) noexcept
    {
        _ctime = time_t(_dtime + _ctime);
        return _ctime;
    }
    inline const timespec &operator+=(timespec &_timespec,
        const DTime &_dtime) noexcept
    {
        _timespec = timespec(_dtime + _timespec);
        return _timespec;
    }

    inline DTime::DTimeType operator-=(DTime::DTimeType &_time, const DTime _dtime) noexcept
    {
        _time = DTime::DTimeType(_time - _dtime);
        return _time;
    }
    inline time_t operator-=(time_t &_ctime,
        const DTime &_dtime) noexcept
    {
        _ctime = time_t(_ctime - _dtime);
        return _ctime;
    }
    inline const timespec &operator-=(timespec &_timespec,
        const DTime &_dtime) noexcept
    {
        _timespec = timespec(_timespec - _dtime);
        return _timespec;
    }

    inline DTime operator""_d(size_t _day) noexcept
    {
        return DTime((DTime::DTimeType)_day * 24);
    }
    inline DTime operator""_h(size_t _hour) noexcept
    {
        return DTime((DTime::DTimeType)_hour * 3600);
    }
    inline DTime operator""_m(size_t _minute) noexcept
    {
        return DTime((DTime::DTimeType)_minute * 60);
    }
    inline DTime operator""_s(size_t _second) noexcept
    {
        return DTime((DTime::DTimeType)_second);
    }
    inline DTime operator""_ms(size_t _milisecond) noexcept
    {
        return DTime((DTime::DTimeType)_milisecond / 1e3);
    }
    inline DTime operator""_us(size_t _microsecond) noexcept
    {
        return DTime((DTime::DTimeType)_microsecond / 1e6);
    }
    inline DTime operator""_ns(size_t _nanosecond) noexcept
    {
        return DTime((DTime::DTimeType)_nanosecond / 1e9);
    }

    inline DTime GetFileTime(const std::filesystem::path &_filepath)
    {
        return DTime(std::time_t(std::chrono::duration_cast<std::chrono::seconds>(
            std::filesystem::last_write_time(_filepath).time_since_epoch() -
            std::filesystem::file_time_type::clock::now().time_since_epoch() +
            std::chrono::system_clock::now().time_since_epoch())
            .count()));
    }

    template <class CharT>
    std::basic_string<CharT> inttostr(long long _num) noexcept
    {
        return std::basic_string<CharT>();
    }

    template <>
    std::basic_string<char> inttostr(long long _num) noexcept
    {
        return std::to_string(_num);
    }

    template <>
    std::basic_string<wchar_t> inttostr(long long _num) noexcept
    {
        return std::to_wstring(_num);
    }

    template <class CharT>
    DTime StringtoDTime(const std::basic_string<CharT> &_target) noexcept
    {
        auto stoi_ = [](const std::basic_string<CharT> &_target)
        {
            try
            {
                return std::stoul(_target);
            }
            catch (const std::exception &)
            {
                return (unsigned long)-1;
            }
        };
        auto tempstr = _target;
        std::vector<std::basic_string<CharT>> result, dayresult, timeresult;
        using DUtility::split;
        bool isnegative = false;
        if (tempstr.front() == (CharT)'-')  // 
        {
            isnegative = true;
            tempstr.erase(0, 1);
        }
        if (split(result, tempstr, (CharT)' '))
        {
            const auto resnum = result.size();
            if (resnum == 2)
            {
                if ((split(dayresult, result[0], '/') ||
                    split(dayresult, result[0], '-')) &&
                    (dayresult.size() != 3))
                    return DTime();
                if (split(timeresult, result[1], ':') &&
                    (timeresult.size() != 3))
                    return DTime();
                split(timeresult, timeresult[2], '.');
                timeresult.erase(timeresult.begin() + 2);
            }
            else if (resnum < 2)
            {
                if ((split(dayresult, result[0], '/') ||
                    split(dayresult, result[0], '-')) &&
                    (dayresult.size() != 3))
                {
                    if (split(timeresult, result[1], ':') &&
                        (timeresult.size() != 3))
                        return DTime();
                    split(timeresult, timeresult[2], '.');
                    timeresult.erase(timeresult.begin() + 2);
                }
            }
            else
                return DTime();
        }
        else
        {
            if ((split(dayresult, result[0], '/') ||
                split(dayresult, result[0], '-')) &&
                (dayresult.size() != 3))
            {
                if (split(timeresult, result[1], ':') &&
                    (timeresult.size() != 3))
                    return DTime();
                split(timeresult, timeresult[2], '.');
                timeresult.erase(timeresult.begin() + 2);
            }
        }

        unsigned long day[3] = {0}, time[4] = {0};
        for (int i = 0; i < dayresult.size(); ++i)
            day[i] = stoi_(dayresult[i]);
        for (int i = 0; i < timeresult.size(); ++i)
            time[i] = stoi_(timeresult[i]);
        if(day[0] < 100)    // Get current century. If year was input as XX, set the year as current century.
        {
            std::tm tm_;
            std::time_t t_ = std::time(nullptr);
            localtime_s(&tm_, &t_);
            day[0] += ((int)((tm_.tm_year + 1900) / 100)) * 100;
        }

        if (0 >= (int)(day[1] -= 2))  /* 1..12 -> 11,12,1..10 */
        {    
            day[1] += 12;      /* Puts Feb last since it has leap day */
            day[0] -= 1;
        }
        
        return (DTime)(((((
            day[0] / 4 - day[0] / 100 + day[0] / 400) +
            (day[0] - 1) * 365 +
            day[1] * 367 / 12 + 31 + 28 - 30 +
            day[2] - 1 - 693595/* since 1900 */
            ) * 24 + time[0]
            ) * 60 + time[1]
            ) * 60 + time[2] +
            (double)time[3] / 1000);
       
    }

   

} // namespace TimeLibary

#endif // _TIMELIB_HPP
