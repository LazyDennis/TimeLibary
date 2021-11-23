#include <iostream>
#include "TimeLibary.hpp"
//#include "StopWatch.hpp"
//#include <DUtilLib.hpp>


int main()
{
    std::cout << TimeLibary::DTime::Now().string<char>("yy/mm/dd", TimeLibary::DTime::Local);

   

    return 0;
}