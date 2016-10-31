#include "Scene.hpp"

namespace ImasiEngine
{
    Scene::Scene()
    {
        _context = nullptr;
    }

    Scene::~Scene()
    {

    }

    void Scene::setContext(EngineContext* context)
    {
        _context = context;
    }

    void Scene::loop()
    {
        update(_frameClock.restart().asSeconds());
        render();
    }
}
