#ifndef IMASIGAME_INPUTHANDLER_HPP
#define IMASIGAME_INPUTHANDLER_HPP

#include "SFML/Window/Event.hpp"

namespace Imasi
{
    class InputHandler
    {
    protected:

        bool _keyboardKeyStates[sf::Keyboard::Key::KeyCount];

        sf::Vector2i _mousePosition;
        sf::Vector2i _mouseLastPosition;
        bool _mouseButtonStates[sf::Mouse::Button::ButtonCount];

    public:

        InputHandler();
        virtual ~InputHandler();

        virtual void processWindowEvent(const sf::Event& event);
        virtual void resetStates();

        bool isKeyPressed(sf::Keyboard::Key key) const;

        sf::Vector2i getMousePosition() const;
        void setMousePosition(sf::Vector2i position);
        sf::Vector2i getMouseMovement() const;
        void resetMouseMovement();
        bool isMouseButtonPressed(sf::Mouse::Button button) const;
    };
}

#endif
