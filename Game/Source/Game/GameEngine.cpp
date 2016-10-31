#include "GameEngine.hpp"

#include "../Scenes/DemoScene.hpp"

namespace Imasi
{
    GameEngine::GameEngine() : Engine()
    {
        setupWindow("Woo");

        _context = new GameContext();
        _context->level = 666;

        setScene(new DemoScene(_context));
    }

    GameEngine::~GameEngine()
    {
        delete _context;
    }
}
