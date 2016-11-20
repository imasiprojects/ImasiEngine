#ifndef IMASIENGINE_SCENE_HPP
#define IMASIENGINE_SCENE_HPP

#include <queue>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "EngineEvent.hpp"
#include "SceneEvent.hpp"

namespace ImasiEngine
{

    class Scene
    {
    private:

        bool _isActive;

    protected:

        sf::Clock _sceneClock, _frameClock;

        std::queue<SceneEvent> _eventQueue;

    public:

        Scene();
        virtual ~Scene();

        void pushEvent(SceneEvent event);
        bool pollEvent(SceneEvent& event);

        virtual void processWindowEvent(const sf::Event& event) = 0;
        virtual void processEngineEvent(const EngineEvent& event) = 0;

        virtual void loop();
        virtual void update();
        virtual void update(const float deltaTime) = 0;
        virtual void render() = 0;

        bool isActive() const;
        void setActive(bool isActive = true);
    };
}
#endif
