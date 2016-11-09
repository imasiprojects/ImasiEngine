#ifndef IMASIENGINE_WINDOW_HPP
#define IMASIENGINE_WINDOW_HPP

#include <SFML/Graphics.hpp>

namespace ImasiEngine
{
    class Window : public sf::RenderWindow
    {
    private:

        bool focus;

    public:

        Window(const sf::VideoMode& size, const std::string& title, const unsigned int style, const sf::ContextSettings& contextSettings);

        bool isFocused() const;
        void setFocus(bool focus);
    };
}

#endif
