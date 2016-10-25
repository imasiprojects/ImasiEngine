#include "../../ImasiEngine/Source/Engine.hpp"

using namespace ImasiEngine;

int main()
{
    Engine game;
    game.create("Woo", 800, 600, sf::Style::Close);
    game.run();
}