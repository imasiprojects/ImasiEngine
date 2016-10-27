#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

namespace ImasiEngine
{
    namespace SfmlOpengl
    {
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
