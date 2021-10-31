#include "TimeLibary.hpp"
#include <iostream>

int main()
{
    using namespace TimeLibary;
    BasicTime time0(timespec({500, 123456000}));
    BasicTime time1(std::time_t(700));
    auto time2 = time0 + time1;
    auto time3 = time0 - time1;

    auto i = time2.IntegerSecond() + time3.IntegerSecond();

    std::cout << i << std::endl;

    std::cout << time2.Seconds() << std::endl;
    std::cout << time3.Seconds() << std::endl;

    FileTime ft(std::filesystem::path(R"(D:\Dennis\CodeSpace\Cpp_Project\easonlee66-stopwatch-master.zip)"));
    std::cout << ft.FileTimeString() << std::endl;

    return 0;
}