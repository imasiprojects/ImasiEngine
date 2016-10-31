#pragma once

#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "EngineContext.hpp"

namespace ImasiEngine
{
    class Scene
    {
    protected:

        EngineContext* _context;
        sf::Clock _sceneClock, _frameClock;

    public:

        Scene();
        virtual ~Scene();

        virtual void setContext(EngineContext* renderTarget);

        virtual void processWindowEvent(const sf::Event& event) = 0;
        
        virtual void loop();
        virtual void update(const double deltaTime) = 0;
        virtual void render() = 0;
    };
}
