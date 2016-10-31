#pragma once

#include "Engine/Window.hpp"
#include "Engine/Scene.hpp"
#include "Engine/EngineContext.hpp"

namespace ImasiEngine
{
    class Engine
    {
    protected:

        Window* _window;
        Scene* _scene;
        EngineContext* _context;

        virtual void setupGlew();
        virtual void setupOpenGL();

        virtual void loop();
        virtual void processWindowEvents();
        virtual void processWindowEvent(const sf::Event event);

    public:

        Engine();
        virtual ~Engine();

        void setContext(EngineContext* context);
        void setScene(Scene* scene);

        void create(const std::string& title, const unsigned int style = sf::Style::Close, const unsigned int width = 800, const unsigned int height = 600);
        void run();
    };
}
