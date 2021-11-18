#include <iostream>
#include "TimeLibary.hpp"
#include "StopWatch.hpp"


int main()
{
    using namespace TimeLibary;
    DTime time;
    time = DTime::now();
    std::cout << time.ToString("%T") << std::endl;

    stopwatch stw;

    stw.Start();

    for (int i = 0; i < 50000; ++i)
        for (int j = 0; j < 50000; ++j)
            if (i == 1000 && j == 100)
                std::cout << i * j << std::endl;

    stw.Pause();
    DTime t = stw.Now();
    time = DTime::now();
    std::cout << time.ToString("%T") << std::endl;
    std::cout << DTime::DTimeType(t) << std::endl;
    std::cout << t.ToString("%T") << std::endl;

    return 0;
}