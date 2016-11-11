#include <iostream>
#include "../../ImasiEngine/Source/Utils/Logger.hpp"

int main()
{
    ImasiEngine::Logger::out << "Hello" << std::endl;
    std::cin.get();

    return 0;
}
