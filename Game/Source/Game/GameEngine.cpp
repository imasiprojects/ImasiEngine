#include "GameEngine.hpp"

#include "../Scenes/DemoScene.hpp"

namespace Imasi
{
    GameEngine::GameEngine()
        : Engine()
    {
        _context = new GameContext();
    }

    GameEngine::~GameEngine()
    {
        delete _context;
    }


    void GameEngine::run()
    {
        setupWindow("Woo");
        _context->window = _window;

        Engine::run(new DemoScene(_context));
        _context->window->close();
    }
}
