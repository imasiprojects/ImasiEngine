#include "GameEngine.hpp"

#include "../Scenes/DemoScene.hpp"
#include "../Services/DemoService.hpp"

namespace Imasi
{
    GameEngine::GameEngine()
        : Engine()
    {
        _context = new GameContext();
        _serviceContainer->add(new DemoService());
    }

    GameEngine::~GameEngine()
    {
        delete _context;
        delete _serviceContainer;
    }


    void GameEngine::run()
    {
        setupWindow("Woo");
        _context->window = _window;

        Engine::run(new DemoScene(_context, _serviceContainer));
        _context->window->close();
    }
}
