#include "DemoEngine.hpp"

#include "../Scenes/DemoScene.hpp"

namespace Imasi
{
    DemoEngine::DemoEngine()
        : Engine()
    {
    }

    DemoEngine::~DemoEngine()
    {
    }


    void DemoEngine::run()
    {
        setupWindow("Woo");

        Engine::run(std::make_unique<DemoScene>());
        _window->close();
    }
}
