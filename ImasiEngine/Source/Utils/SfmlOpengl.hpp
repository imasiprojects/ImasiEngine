#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

namespace ImasiEngine
{
    class SfmlOpengl
    {
    public:

        static void beginSfml(sf::RenderWindow* window)
        {
            window->pushGLStates();
        }

        static void endSfml(sf::RenderWindow* window)
        {
            window->popGLStates();
        }
    };
}