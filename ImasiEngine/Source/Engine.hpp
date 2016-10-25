#pragma once

#include "Graphics/Window.hpp"

namespace ImasiEngine
{
    class Engine
    {
    protected:

        Window* _window;

        virtual void setupGlew();
        virtual void setupOpenGL();

        virtual void loop();
        virtual void processWindowEvents();
        virtual void processWindowEvent(const sf::Event event);

    public:

        Engine();
        virtual ~Engine();

        Window* getWindow() const;

        void create(const std::string& title, const unsigned int width, const unsigned int height, const unsigned int style);
        void run();
    };
}