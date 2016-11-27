#include "InputHandler.hpp"

namespace Imasi
{
    InputHandler::InputHandler()
    {
        InputHandler::resetStates();
    }

    InputHandler::~InputHandler()
    {
    }

    void InputHandler::processWindowEvent(const sf::Event& event)
    {
        switch (event.type)
        {
            case sf::Event::LostFocus:
            {
                resetStates();
                break;
            }

            case sf::Event::KeyPressed:
            {
                _keyboardKeyStates[event.key.code] = true;
                break;
            }

            case sf::Event::KeyReleased:
            {
                _keyboardKeyStates[event.key.code] = false;
                break;
            }

            case sf::Event::MouseMoved:
            {
                sf::Vector2i currentPosition(event.mouseMove.x, event.mouseMove.y);
                sf::Vector2i currentMovement = currentPosition - _mousePosition;

                _mousePosition = currentPosition;
                _mouseMovement += currentMovement;
                break;
            }

            case sf::Event::MouseButtonPressed:
            {
                _mouseButtonStates[event.mouseButton.button] = true;
                break;
            }

            case sf::Event::MouseButtonReleased:
            {
                _mouseButtonStates[event.mouseButton.button] = false;
                break;
            }
        }
    }

    void InputHandler::resetStates()
    {
        for (bool& keyState : _keyboardKeyStates)
        {
            keyState = false;
        }

        for (bool& mouseButtonState : _mouseButtonStates)
        {
            mouseButtonState = false;
        }

        _mousePosition = sf::Vector2i(0, 0);
        _mouseMovement = sf::Vector2i(0, 0);
    }

    bool InputHandler::isKeyPressed(sf::Keyboard::Key key) const
    {
        return _keyboardKeyStates[key];
    }

    sf::Vector2i InputHandler::getMousePosition() const
    {
        return _mousePosition;
    }

    sf::Vector2i InputHandler::getMouseMovement() const
    {
        return _mouseMovement;
    }

    void InputHandler::resetMouseMovement()
    {
        _mouseMovement = sf::Vector2i(0, 0);
    }

    bool InputHandler::isMouseButtonPressed(sf::Mouse::Button button) const
    {
        return _mouseButtonStates[button];
    }
}
