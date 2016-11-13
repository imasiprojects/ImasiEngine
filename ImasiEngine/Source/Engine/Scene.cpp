#include "Scene.hpp"

namespace ImasiEngine
{
    Scene::Scene()
        : _isActive(false)
    {
    }

    Scene::~Scene()
    {
    }

    void Scene::pushEvent(SceneEvent event)
    {
        _eventQueue.push(event);
    }

    bool Scene::pollEvent(SceneEvent& event)
    {
        if (_eventQueue.size() > 0)
        {
            event = _eventQueue.front();
            _eventQueue.pop();

            return true;
        }

        return false;
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

    bool Scene::isActive() const
    {
        return _isActive;
    }

    void Scene::setActive(bool isActive)
    {
        _isActive = isActive;
    }
}
