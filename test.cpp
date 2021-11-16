#include "TimeLibary.hpp"
#include <iostream>

int main()
{
    using namespace TimeLibary;
    BasicTime time;
    time = BasicTime::now();
    std::cout << time.ToString("%D %T");

    return 0;
}