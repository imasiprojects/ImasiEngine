#include "../../ImasiEngine/Source/Engine.hpp"

#include "Scenes/DemoScene.hpp"
#include "Game/GameContext.hpp"
#include "Game.hpp"

int main()
{
    Imasi::GameContext* context = new Imasi::GameContext();
    context->level = 334;

    Imasi::Game game;
    game.create("Woo");
    game.setContext(context);
    game.setScene(new Imasi::DemoScene());
    game.run();

    return 0;
}
