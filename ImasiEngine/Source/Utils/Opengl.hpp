#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#define NULL_ID 0

#ifdef DEBUG

    #define GL(glCall) glCall; do {} while (ImasiEngine::Opengl::checkError(__FILE__, __LINE__, #glCall))

    #define GL_CHECK() do {} while (ImasiEngine::Opengl::checkError(__FILE__, __LINE__))

    #define USING(glObject, body) glObject->bind(glObject); body glObject->unbind()

#else

    #define GL(glCall) glCall

    #define GL_CHECK() 

    #define USING(glObject, body) glObject->bind(glObject); body

#endif

namespace ImasiEngine
{
    namespace Opengl
    {
        void beginSfml(sf::RenderWindow* window);
        void endSfml(sf::RenderWindow* window);

        bool checkError(const char* file, const int line, const char* call = nullptr);
    }
}
