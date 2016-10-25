#include "Window.hpp"

namespace ImasiEngine
{
    Window::Window(const sf::VideoMode& size, const std::string& title, const unsigned int style, const sf::ContextSettings& contextSettings) : RenderWindow(size, title, style, contextSettings)
    {
        this->focus = true;
    }

    bool Window::isFocused() const
    {
        return this->focus;
    }

    void Window::setFocus(bool focus)
    {
        this->focus = focus;
    }
}