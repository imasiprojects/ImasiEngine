#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#define UNBIND 0

#ifdef DEBUG

    #define GL(glCall) do { \
        glCall; \
        ImasiEngine::Opengl::checkError(__FILE__, __LINE__, #glCall); \
    } while (false)

    #define GL_CHECK() do { \
        ImasiEngine::Opengl::checkError(__FILE__, __LINE__); \
    } while (false)

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

        void checkError(const char* file, const int line, const char* call = nullptr);
    }
}
