#include <iostream>

#include "../../ImasiEngine/Source/Engine.hpp"

#include "Game/GameEngine.hpp"

int main()
{
    Imasi::GameEngine game;
    game.run();

    std::cin.get();

    return 0;
}
