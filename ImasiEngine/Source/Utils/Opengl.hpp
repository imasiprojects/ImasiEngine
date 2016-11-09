#ifndef IMASIENGINE_OPENGL_HPP
#define IMASIENGINE_OPENGL_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#define NULL_ID 0

#define BIND(glObjectType, glObject, ...) glObjectType::bind(glObject, __VA_ARGS__)

#ifdef DEBUG

    #define GL(glCall) glCall; do {} while (ImasiEngine::Opengl::checkError(__FILE__, __LINE__, #glCall))

    #define GL_CHECK() do {} while (ImasiEngine::Opengl::checkError(__FILE__, __LINE__))

    #define UNBIND(glObjectType, ...) glObjectType::unbind(__VA_ARGS__)

#else

    #define GL(glCall) glCall

    #define GL_CHECK() 

    #define UNBIND(glObjectType, ...) 

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

#endif