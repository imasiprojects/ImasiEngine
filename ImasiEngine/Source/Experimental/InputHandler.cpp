#include "InputHandler.hpp"

namespace ImasiEngine
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
                _mousePosition = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
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
        _mouseLastPosition = sf::Vector2i(0, 0);
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
        return _mousePosition - _mouseLastPosition;
    }

    void InputHandler::resetMouseMovement()
    {
        _mouseLastPosition = _mousePosition;
    }

    void InputHandler::resetMouseMovement(sf::Vector2i position)
    {
        _mouseLastPosition = position;
    }

    bool InputHandler::isMouseButtonPressed(sf::Mouse::Button button) const
    {
        return _mouseButtonStates[button];
    }
}
