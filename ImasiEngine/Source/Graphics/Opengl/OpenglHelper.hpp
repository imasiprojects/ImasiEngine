#ifndef IMASIENGINE_OPENGLHELPER_HPP
#define IMASIENGINE_OPENGLHELPER_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <GL/glew.h>
#include <glm/glm.hpp>

#define NULL_ID 0

#define BIND(glObjectType, glObject, ...) glObjectType::bind(glObject, __VA_ARGS__)

#ifdef DEBUG

    #define GL(glCall) glCall; do {} while (ImasiEngine::OpenglHelper::checkError(__FILE__, __LINE__, #glCall))

    #define GL_CHECK() do {} while (ImasiEngine::OpenglHelper::checkError(__FILE__, __LINE__))

    #define UNBIND(glObjectType, ...) glObjectType::unbind(__VA_ARGS__)

#else

    #define GL(glCall) glCall

    #define GL_CHECK() 

    #define UNBIND(glObjectType, ...) 

#endif

namespace ImasiEngine
{
    namespace OpenglHelper
    {
        void beginSfml(sf::RenderWindow* window);
        void endSfml(sf::RenderWindow* window);

        bool checkError(const char* file, const int line, const char* call = nullptr);

        template <
            typename T,
            typename = typename std::enable_if<
                std::is_same<T, float>::value
                || std::is_same<T, double>::value
                || std::is_same<T, int>::value
                || std::is_same<T, unsigned int>::value
                || std::is_same<T, short>::value
                || std::is_same<T, unsigned short>::value

                || std::is_same<T, glm::vec2>::value
                || std::is_same<T, glm::vec3>::value
                || std::is_same<T, glm::vec4>::value
                || std::is_same<T, glm::mat2>::value
                || std::is_same<T, glm::mat3>::value
                || std::is_same<T, glm::mat4>::value
            >::type
        >
        unsigned int getGLType()
        {
            if (std::is_same<T, float>::value
                || std::is_same<T, glm::vec2>::value
                || std::is_same<T, glm::vec3>::value
                || std::is_same<T, glm::vec4>::value
                || std::is_same<T, glm::mat2>::value
                || std::is_same<T, glm::mat3>::value
                || std::is_same<T, glm::mat4>::value)
            {
                return GL_FLOAT;
            }
            if (std::is_same<T, double>::value)
            {
                return GL_DOUBLE;
            }
            if (std::is_same<T, int>::value)
            {
                return GL_INT;
            }
            if (std::is_same<T, unsigned int>::value)
            {
                return GL_UNSIGNED_INT;
            }
            if (std::is_same<T, short>::value)
            {
                return GL_SHORT;
            }
            if (std::is_same<T, unsigned short>::value)
            {
                return GL_UNSIGNED_SHORT;
            }

            return 0;
        }

        template<unsigned int N>
        struct GLType
        {
        };
        template<>
        struct GLType<GL_FLOAT>
        {
            typedef float type;
        };
        template<>
        struct GLType<GL_DOUBLE>
        {
            typedef double type;
        };
        template<>
        struct GLType<GL_INT>
        {
            typedef int type;
        };
        template<>
        struct GLType<GL_UNSIGNED_INT>
        {
            typedef unsigned int type;
        };
        template<>
        struct GLType<GL_SHORT>
        {
            typedef short type;
        };
        template<>
        struct GLType<GL_UNSIGNED_SHORT>
        {
            typedef unsigned short type;
        };
    }
}

#endif
