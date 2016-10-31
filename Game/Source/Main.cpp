#include "../../ImasiEngine/Source/Engine.hpp"
#include "Scenes/DemoScene.hpp"
#include "Game.hpp"

int main()
{
    Imasi::Game game;
    game.create("Woo");
    game.setScene(new Imasi::DemoScene());
    game.run();

    return 0;
}
