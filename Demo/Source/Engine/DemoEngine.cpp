#include "DemoEngine.hpp"

#include "../Scenes/DemoScene.hpp"

namespace Imasi
{
    DemoEngine::DemoEngine()
        : Engine()
    {
        _context = new DemoContext();
    }

    DemoEngine::~DemoEngine()
    {
        delete _context;
    }


    void DemoEngine::run()
    {
        setupWindow("Woo");
        _context->window = _window;

        Engine::run(new DemoScene(_context));
        _context->window->close();
    }
}
