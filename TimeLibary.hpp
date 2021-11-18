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

#define TIMESPECTOD(x) (x.tv_sec + x.tv_nsec / DTimeType(1e9))

namespace TimeLibary
{
    using std::time_t;
    using std::timespec;
    class DTime
    {
    public:
        typedef double DTimeType;

    private:
        DTimeType time_;

    public:
        DTime() noexcept : time_(DTimeType(0)) {}
        DTime(const DTime &_other) noexcept : time_(_other.time_) {}
        DTime(DTime &&_other) noexcept : time_(_other.time_) {}
        DTime(DTimeType _time) noexcept : time_(_time) {}
        explicit DTime(time_t _ctime) noexcept : time_(_ctime) {}
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
            time_ = _ctime;
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
        
        std::string ToString(const std::string &_format, bool _showmsec = true) const noexcept
        {
            std::tm *TimeStruct;
            std::string timestring(100, '\0');
            time_t temptime = time_t(time_);
            TimeStruct = std::gmtime(&temptime);
            std::strftime(timestring.data(), 100, _format.c_str(), TimeStruct);
            if (_showmsec && (
                ~_format.find("%S") ||
                ~_format.find("%s") ||
                ~_format.find("%T") ||
                ~_format.find("%s")))
            {
                timestring.pop_back();
                timestring += "." + std::to_string(int((time_ - int(time_)) * 1000));
            }
            return timestring;
        }

        static DTime now()
        {
            timespec temptimespec;
            auto result = std::timespec_get(&temptimespec, TIME_UTC);
            if (TIME_UTC == result)
                return DTime(temptimespec);
            else
                return DTime(DTimeType(0));
        }

    }; // class DTime

    DTime operator+(DTime::DTimeType _time, const DTime &_dtime) noexcept
    {
        return _dtime + _time;
    }
    DTime operator+(time_t _ctime, const DTime &_dtime) noexcept
    {
        return _dtime + _ctime;
    }
    DTime operator+(const timespec &_timespec,
        const DTime &_dtime) noexcept
    {
        return _dtime + _timespec;
    }

    DTime operator-(DTime::DTimeType _time, const DTime &_dtime) noexcept
    {
        return DTime(_time) - _dtime;
    }
    DTime operator-(time_t _ctime, const DTime &_dtime) noexcept
    {
        return DTime(_ctime) - _dtime;
    }
    DTime operator-(const timespec &_timespec,
        const DTime &_dtime) noexcept
    {
        return DTime(_timespec) - _dtime;
    }

    DTime operator*(long _times, const DTime &_dtime) noexcept
    {
        return _dtime * _times;
    }

    DTime::DTimeType operator+=(DTime::DTimeType & _time, const DTime &_dtime)
    {
        _time = DTime::DTimeType(_time + _dtime);
        return _time;
    }

    time_t operator+=(time_t &_ctime,
        const DTime &_dtime) noexcept
    {
        _ctime = time_t(_dtime + _ctime);
        return _ctime;
    }
    const timespec &operator+=(timespec &_timespec,
        const DTime &_dtime) noexcept
    {
        _timespec = timespec(_dtime + _timespec);
        return _timespec;
    }

    DTime::DTimeType operator-=(DTime::DTimeType &_time, const DTime _dtime) noexcept
    {
        _time = DTime::DTimeType(_time - _dtime);
        return _time;
    }
    time_t operator-=(time_t &_ctime,
        const DTime &_dtime) noexcept
    {
        _ctime = time_t(_ctime - _dtime);
        return _ctime;
    }
    const timespec &operator-=(timespec &_timespec,
        const DTime &_dtime) noexcept
    {
        _timespec = timespec(_timespec - _dtime);
        return _timespec;
    }


    DTime GetFileTime(const std::filesystem::path &_FilePath)
    {
        return DTime(std::time_t(std::chrono::duration_cast<std::chrono::seconds>(
            std::filesystem::last_write_time(_FilePath).time_since_epoch() -
            std::filesystem::file_time_type::clock::now().time_since_epoch() +
            std::chrono::system_clock::now().time_since_epoch())
            .count()));
    }

} // namespace TimeLibary

#endif // _TIMELIB_HPP
