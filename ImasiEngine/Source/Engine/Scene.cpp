#include "Scene.hpp"

namespace ImasiEngine
{
    Scene::Scene()
    {
    }

    Scene::~Scene()
    {
    }

    void Scene::pushEvent(SceneEvent event)
    {
        _eventQueue.push(event);
    }

    SceneEvent Scene::popEvent()
    {
        SceneEvent event = _eventQueue.front();
        _eventQueue.pop();
        return event;
    }

    void Scene::loop()
    {
        update(_frameClock.restart().asSeconds());
        render();
    }

    void Scene::update()
    {
        update(_frameClock.restart().asSeconds());
    }
}
