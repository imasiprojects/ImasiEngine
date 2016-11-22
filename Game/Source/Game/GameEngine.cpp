#include "GameEngine.hpp"

#include "../Scenes/DemoScene.hpp"

namespace Imasi
{
    GameEngine::GameEngine()
        : Engine()
    {
        _context = new GameContext();
        _serviceContainer = new GameServiceContainer();
        _serviceContainer->myDemoService = new DemoService();
    }

    GameEngine::~GameEngine()
    {
        delete _context;
        delete _serviceContainer->myDemoService;
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
