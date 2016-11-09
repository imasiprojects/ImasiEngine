#ifndef IMASIENGINE_SCENE_HPP
#define IMASIENGINE_SCENE_HPP

#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

namespace ImasiEngine
{
    class Scene
    {
    protected:

        sf::Clock _sceneClock, _frameClock;

    public:

        Scene();
        virtual ~Scene();

        virtual void processWindowEvent(const sf::Event& event) = 0;
        
        virtual void loop();
        virtual void update(const double deltaTime) = 0;
        virtual void render() = 0;
    };
}
#endif
