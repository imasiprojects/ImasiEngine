#include "../../ImasiEngine/Source/Engine.hpp"
#include "Scenes/DemoScene.hpp"

int main()
{
    ImasiEngine::Engine game;
    game.create("Woo");
    game.setScene(new Imasi::DemoScene());
    game.run();

    return 0;
}
