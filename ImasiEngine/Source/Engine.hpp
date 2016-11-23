#ifndef IMASIENGINE_ENGINE_HPP
#define IMASIENGINE_ENGINE_HPP

#include <list>

#include "Engine/Window.hpp"
#include "Engine/Scene.hpp"
#include "Engine/Services/ServiceContainer.hpp"

namespace ImasiEngine
{
    class Engine
    {
    private:

        void pushScene(Scene* scene);
        void popScene();

    protected:

        Window* _window;
        std::list<Scene*> _scenes;
        ServiceContainer _serviceContainer;

        void setupWindow(const std::string& title, const unsigned int style = sf::Style::Close, const unsigned int width = 800, const unsigned int height = 600);
        virtual void setupGlew();
        virtual void setupOpenGL();

        virtual void loop();
        virtual void processWindowEvents();
        virtual void processWindowEvent(sf::Event event);

        virtual void processSceneEvents();
        virtual void processSceneEvent(SceneEvent event);

    public:

        Engine();
        virtual ~Engine();

        void run(Scene* newScene);
    };
}

#endif
