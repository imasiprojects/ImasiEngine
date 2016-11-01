#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#define UNBIND 0
#define UNSET -1

#ifdef DEBUG

    #define GL(glCall) glCall; \
        do {} while (ImasiEngine::Opengl::checkError(__FILE__, __LINE__, #glCall))

    #define GL_CHECK() do {} while (ImasiEngine::Opengl::checkError(__FILE__, __LINE__))

#else

    #define GL(glCall) glCall

    #define GL_CHECK() 

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
