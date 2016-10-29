#pragma once

#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace ImasiEngine
{
    class Scene
    {
    protected:

        sf::RenderTarget* _renderTarget;
        sf::Clock _sceneClock, _frameClock;

    public:

        Scene();
        virtual ~Scene();

        void setRenderTarget(sf::RenderTarget* renderTarget);

        virtual void processWindowEvent(const sf::Event& event) = 0;
        
        virtual void loop();
        virtual void update(const double deltaTime) = 0;
        virtual void render() = 0;
    };
}
