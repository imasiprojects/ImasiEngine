#include "GameEngine.hpp"

#include "../Scenes/DemoScene.hpp"

namespace Imasi
{
    GameEngine::GameEngine() : Engine()
    {
        setupWindow("Woo");

        _context = new GameContext();
        _context->window = _window;
    }

    GameEngine::~GameEngine()
    {
        delete _context;
    }


    void GameEngine::run()
    {
        Engine::run(new DemoScene(_context));
    }
}
