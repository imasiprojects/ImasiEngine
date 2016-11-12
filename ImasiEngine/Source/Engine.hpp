#ifndef IMASIENGINE_ENGINE_HPP
#define IMASIENGINE_ENGINE_HPP

#include <list>

#include "Engine/Window.hpp"
#include "Engine/Scene.hpp"

namespace ImasiEngine
{
    class Engine
    {
    protected:

        Window* _window;
        std::list<Scene*> _scenes;

        void setupWindow(const std::string& title, const unsigned int style = sf::Style::Close, const unsigned int width = 800, const unsigned int height = 600);
        virtual void setupGlew();
        virtual void setupOpenGL();

        virtual void loop();
        virtual void processWindowEvents();
        virtual void processWindowEvent(sf::Event event);

        virtual void processSceneEvents();
        virtual void processSceneEvent(EngineEvent event);

    public:

        Engine();
        virtual ~Engine();

        void run(Scene* scene);
    };
}

#endif
