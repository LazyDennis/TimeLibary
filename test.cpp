#include <iostream>
#include "TimeLibary.hpp"
//#include "StopWatch.hpp"
//#include <DUtilLib.hpp>


int main()
{
    std::cout << TimeLibary::DTime::Now().string<char>("yy/mm/dd", TimeLibary::DTime::Local) << std::endl;

    std::cout << TimeLibary::StringtoDTime((std::string)"12/8/20 20:34:59.879").string((std::string)"YY/MM/DD") << std::endl;

     return 0;
}