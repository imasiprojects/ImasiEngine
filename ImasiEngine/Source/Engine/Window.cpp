#include "Window.hpp"

namespace ImasiEngine
{
    Window::Window(const sf::VideoMode& size, const std::string& title, const unsigned int style, const sf::ContextSettings& contextSettings) : RenderWindow(size, title, style, contextSettings)
    {
        this->_hasFocus = true;
    }

    bool Window::hasFocus() const
    {
        return this->_hasFocus;
    }

    void Window::setFocus(bool focus)
    {
        this->_hasFocus = focus;
    }
}
