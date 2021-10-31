#pragma once
#ifndef _TIMELIB_HPP
#define _TIMELIB_HPP

#include <chrono>
#include <ctime>
#include <string>
#include <filesystem>

namespace TimeLibary
{
    using std::time_t;
    using std::timespec;
    class BasicTime : protected timespec
    {
    private:
        static const long MaxNSec = 1e9 - 1l;            // tv_nsec in [0, 999999999]
        static const time_t MaxSec = 0x7FFFFFFFFFFFFFFFll; // maximum value of time_t type.

    public:
        BasicTime() noexcept = default;
        BasicTime(const BasicTime &_OtherBasicTime) = default;
        BasicTime(BasicTime &&_OtherBasicTime) = default;
        explicit BasicTime(time_t _CTime) noexcept : timespec({_CTime, 0}) {}
        explicit BasicTime(const timespec &_TimeSpec) noexcept : timespec(_TimeSpec) {}

        ~BasicTime() = default;

        static BasicTime now()
        {
            BasicTime TempTime;
            std::timespec_get(&TempTime, TIME_UTC);
            return TempTime;
        }

        const BasicTime &operator=(const BasicTime &_OtherBasicTime) noexcept
        {
            tv_sec = _OtherBasicTime.tv_sec;
            tv_nsec = _OtherBasicTime.tv_nsec;
            return *this;
        }
        const BasicTime &operator=(BasicTime &&_OtherBasicTime) noexcept
        {
            tv_sec = _OtherBasicTime.tv_sec;
            tv_nsec = _OtherBasicTime.tv_nsec;
            return *this;
        }
        const BasicTime &operator=(time_t _CTime) noexcept
        {
            tv_sec = _CTime;
            return *this;
        }
        const BasicTime &operator=(const timespec &_TimeSpec) noexcept
        {
            tv_nsec = _TimeSpec.tv_nsec;
            tv_sec = _TimeSpec.tv_sec;
            return *this;
        }

        operator time_t() noexcept { return tv_sec; }
        operator timespec() noexcept { return timespec({tv_sec, tv_nsec}); }

        BasicTime operator+(const BasicTime &_OtherBasicTime) const noexcept
        {
            BasicTime TempTime;
            long long TempNSec = long long(tv_nsec) + _OtherBasicTime.tv_nsec;
            auto Carrybit = TempNSec / (MaxNSec + 1);
            if (MaxSec - _OtherBasicTime.tv_sec - Carrybit > tv_sec) // check if plus result overflows.
            {
                TempTime.tv_nsec = TempNSec % (MaxNSec + 1);
                TempTime.tv_sec = tv_sec + Carrybit +
                                  _OtherBasicTime.tv_sec;
            }
            else
            {
                TempTime.tv_sec = MaxSec;
                TempTime.tv_nsec = MaxNSec;
            }
            return TempTime;
        }
        BasicTime operator+(time_t _CTime) const noexcept
        {
            return BasicTime({tv_sec + _CTime, tv_nsec});
        }
        BasicTime operator+(const timespec &_TimeSpec) const noexcept
        {
            return *this + BasicTime(_TimeSpec);
        }

        BasicTime operator-(const BasicTime &_OtherBasicTime) const noexcept
        {
            BasicTime TempTime;
            long long Borrowbit = (tv_nsec < _OtherBasicTime.tv_nsec),
                      SecondSign = (~MaxSec) & tv_sec, // save sign of tv_sec in SecondSign
                TempSec = tv_sec & MaxSec;             // absolute value of tv_sec.
            if (MaxSec - TempSec - Borrowbit > (_OtherBasicTime.tv_sec & MaxSec))
            {
                TempTime.tv_sec = tv_sec - Borrowbit - _OtherBasicTime.tv_sec;
                TempTime.tv_nsec = long long(tv_nsec) - _OtherBasicTime.tv_nsec +
                                   (MaxNSec + 1) * Borrowbit;
            }
            else
            {
                TempTime.tv_sec = MaxSec | SecondSign;
                TempTime.tv_nsec = MaxNSec;
            }
            return TempTime;
        }
        BasicTime operator-(time_t _CTime) const noexcept
        {
            return BasicTime({tv_sec - _CTime, tv_nsec});
        }
        BasicTime operator-(const timespec &_TimeSpec) const noexcept
        {
            return *this - BasicTime(_TimeSpec);
        }

        BasicTime operator*(long _Times) const noexcept
        {
            BasicTime TempTime;
            long long TempNSec = (long long)tv_nsec * _Times;
            TempTime.tv_sec = tv_sec + TempNSec / (MaxNSec + 1);
            TempTime.tv_nsec = tv_nsec + TempNSec % (MaxNSec + 1);
            return TempTime;
        }
        BasicTime operator/(long _Divisor) const noexcept
        {
            BasicTime TempTime;
            if (_Divisor)
            {
                TempTime.tv_sec = tv_sec / _Divisor;
                TempTime.tv_nsec = (tv_sec % _Divisor * (MaxNSec + 1) + tv_nsec) /
                                   _Divisor;
            }
            else
            {
                TempTime.tv_sec = MaxSec;
                TempTime.tv_nsec = MaxNSec;
            }
            return TempTime;
        }

        const BasicTime &operator+=(const BasicTime &_OtherBasicTime) noexcept
        {
            *this = *this + _OtherBasicTime;
            return *this;
        }
        const BasicTime &operator+=(time_t _CTime) noexcept
        {
            tv_sec += _CTime;
            return *this;
        }
        const BasicTime &operator+=(const timespec &_TimeSpec) noexcept
        {
            *this = *this + _TimeSpec;
            return *this;
        }

        const BasicTime &operator-=(const BasicTime &_OtherBasicTime) noexcept
        {
            *this = *this - _OtherBasicTime;
            return *this;
        }
        const BasicTime &operator-=(time_t _CTime) noexcept
        {
            tv_sec -= _CTime;
            return *this;
        }
        const BasicTime &operator-=(const timespec &_TimeSpec) noexcept
        {
            *this = *this - _TimeSpec;
            return *this;
        }

        const BasicTime &operator*=(long _Times) noexcept
        {
            *this = *this * _Times;
            return *this;
        }
        const BasicTime &operator/=(long _Divisor) noexcept
        {
            *this = *this / _Divisor;
            return *this;
        }

        long NanoSecond() const noexcept { return tv_nsec; }
        void NanoSecond(long _nsec) noexcept
        {
            tv_nsec = _nsec % (MaxNSec + 1);
            tv_sec += (_nsec / (MaxNSec + 1));
            return;
        }

        time_t IntegerSecond() const noexcept { return tv_sec; }
        void IntegerSecond(time_t _sec) noexcept { tv_sec = _sec; }

        long double Seconds() const noexcept
        {
            return tv_sec + tv_nsec / (long double)(MaxNSec + 1);
        }
        void Seconds(long double _Seconds) noexcept
        {
            tv_sec = time_t(_Seconds);
            tv_nsec = long((_Seconds - tv_sec) * (MaxNSec + 1));
            return;
        }

        std::string TimeString(/*const CharT *_format*/) const noexcept
        {
            std::tm *TimeStruct;
            TimeStruct = localtime(&this->tv_sec);
            return std::to_string(TimeStruct->tm_year + 1900) + "/" + 
                std::to_string(TimeStruct->tm_mon + 1) + "/" + 
                std::to_string(TimeStruct->tm_mday);
        }

        std::wstring TimeWString(/*const CharT *_format*/) const noexcept
        {
            std::tm *TimeStruct;
            TimeStruct = localtime(&this->tv_sec);
            return std::to_wstring(TimeStruct->tm_year + 1900) + L"/" + 
                std::to_wstring(TimeStruct->tm_mon + 1) + L"/" + 
                std::to_wstring(TimeStruct->tm_mday);
        }

        friend const timespec &operator+=(
            timespec &_TimeSpec, const BasicTime &_BasicTime) noexcept;
        friend const timespec &operator-=(
            timespec &_TimeSpec, const BasicTime &_BasicTime) noexcept;
        friend int timespec_get(BasicTime &_BasicTime) noexcept;

    }; // class BasicTime

    BasicTime operator+(time_t _CTime, const BasicTime &_BasicTime) noexcept
    {
        return _BasicTime + _CTime;
    }
    BasicTime operator+(const timespec &_TimeSpec,
                        const BasicTime &_BasicTime) noexcept
    {
        return _BasicTime + _TimeSpec;
    }

    BasicTime operator-(time_t _CTime, const BasicTime &_BasicTime) noexcept
    {
        return BasicTime(_CTime) - _BasicTime;
    }
    BasicTime operator-(const timespec &_TimeSpec,
                        const BasicTime &_BasicTime) noexcept
    {
        return BasicTime(_TimeSpec) - _BasicTime;
    }

    BasicTime operator*(long _Times, const BasicTime &_BasicTime) noexcept
    {
        return _BasicTime * _Times;
    }

    time_t operator+=(time_t &_CTime,
                      const BasicTime &_BasicTime) noexcept
    {
        _CTime = time_t(_BasicTime + _CTime);
        return _CTime;
    }
    const timespec &operator+=(timespec &_TimeSpec,
                               const BasicTime &_BasicTime) noexcept
    {
        _TimeSpec = timespec(_TimeSpec + _BasicTime);
        return _TimeSpec;
    }

    time_t operator-=(time_t &_CTime,
                      const BasicTime &_BasicTime) noexcept
    {
        _CTime = time_t(_CTime - _BasicTime);
        return _CTime;
    }
    const timespec &operator-=(timespec &_TimeSpec,
                               const BasicTime &_BasicTime) noexcept
    {
        _TimeSpec = timespec(_TimeSpec - _BasicTime);
        return _TimeSpec;
    }

    int timespec_get(BasicTime &_BasicTime) noexcept
    {
        return std::timespec_get(&_BasicTime, TIME_UTC);
    }

    BasicTime GetFileTime(const std::filesystem::path &_FilePath)
    {
        return BasicTime(std::time_t(std::chrono::duration_cast<std::chrono::seconds>(
            std::filesystem::last_write_time(_FilePath).time_since_epoch() -
            std::filesystem::file_time_type::clock::now().time_since_epoch() +
            std::chrono::system_clock::now().time_since_epoch())
            .count()));
    }

} // namespace TimeLibary

#endif // _TIMELIB_HPP
