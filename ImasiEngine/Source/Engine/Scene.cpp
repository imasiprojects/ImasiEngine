#include "Scene.hpp"

namespace ImasiEngine
{
    Scene::Scene()
    {
        _renderTarget = nullptr;
    }

    Scene::~Scene()
    {

    }

    void Scene::setRenderTarget(sf::RenderTarget* renderTarget)
    {
        _renderTarget = renderTarget;
    }

    void Scene::loop()
    {
        update(_frameClock.restart().asSeconds());
        render();
    }
}
