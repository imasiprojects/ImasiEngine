#include "Scene.hpp"

namespace ImasiEngine
{
    Scene::Scene()
    {

    }

    Scene::~Scene()
    {

    }

    void Scene::loop()
    {
        update(_frameClock.restart().asSeconds());
        render();
    }
}
