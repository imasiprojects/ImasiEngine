#ifndef IMASIENGINE_INPUTHANDLER_HPP
#define IMASIENGINE_INPUTHANDLER_HPP

#include <SFML/Window/Event.hpp>

namespace ImasiEngine
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
        sf::Vector2i getMouseMovement() const;
        void resetMouseMovement();
        void resetMouseMovement(sf::Vector2i position);
        bool isMouseButtonPressed(sf::Mouse::Button button) const;
    };
}

#endif
