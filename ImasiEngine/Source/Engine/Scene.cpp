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

    void Scene::pushEvent(SceneEvent&& event)
    {
        _eventQueue.emplace(std::move(event));
    }

    bool Scene::pollEvent(SceneEvent& event)
    {
        if (_eventQueue.size() > 0)
        {
            event = std::move(_eventQueue.front());
            _eventQueue.pop();

            return true;
        }

        return false;
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
