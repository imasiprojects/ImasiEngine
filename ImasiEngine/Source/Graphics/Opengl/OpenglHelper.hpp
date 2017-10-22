#ifndef IMASIENGINE_OPENGLHELPER_HPP
#define IMASIENGINE_OPENGLHELPER_HPP

#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "BindGuard.hpp"
#include "Enums/DataType.hpp"

#define NULL_ID 0

#ifdef DEBUG

    #define GL(glCall) glCall; do {} while (ImasiEngine::OpenglHelper::checkError(__FILE__, __LINE__, #glCall))

    #define GL_CHECK() do {} while (ImasiEngine::OpenglHelper::checkError(__FILE__, __LINE__))

#else

    #define GL(glCall) glCall

    #define GL_CHECK() 

#endif

namespace ImasiEngine
{
    namespace OpenglHelper
    {
        template <typename T, typename... TArgs>
        inline constexpr BindGuard<T, TArgs...> makeBindGuard(const T& object, TArgs&&... args)
        {
            return std::move(BindGuard<T, TArgs...>(object, std::forward<TArgs>(args)...));
        }

        void beginSfml(sf::RenderTarget& renderTarget);
        void endSfml(sf::RenderTarget& renderTarget);

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
        GLEnums::DataType getGLType()
        {
            if (std::is_same<T, float>::value
                || std::is_same<T, glm::vec2>::value
                || std::is_same<T, glm::vec3>::value
                || std::is_same<T, glm::vec4>::value
                || std::is_same<T, glm::mat2>::value
                || std::is_same<T, glm::mat3>::value
                || std::is_same<T, glm::mat4>::value)
            {
                return GLEnums::DataType::Float;
            }

            if (std::is_same<T, double>::value)
            {
                return GLEnums::DataType::Double;
            }

            if (std::is_same<T, int>::value)
            {
                return GLEnums::DataType::Int;
            }

            if (std::is_same<T, unsigned int>::value)
            {
                return GLEnums::DataType::UnsignedInt;
            }

            if (std::is_same<T, short>::value)
            {
                return GLEnums::DataType::Short;
            }

            if (std::is_same<T, unsigned short>::value)
            {
                return GLEnums::DataType::UnsignedShort;
            }

            return GLEnums::DataType::Unknown;
        }


        template<GLEnums::DataType T>
        struct GLType
        {
        };

        template<>
        struct GLType<GLEnums::DataType::Float>
        {
            typedef float type;
        };

        template<>
        struct GLType<GLEnums::DataType::Double>
        {
            typedef double type;
        };

        template<>
        struct GLType<GLEnums::DataType::Int>
        {
            typedef int type;
        };

        template<>
        struct GLType<GLEnums::DataType::UnsignedInt>
        {
            typedef unsigned int type;
        };

        template<>
        struct GLType<GLEnums::DataType::Short>
        {
            typedef short type;
        };

        template<>
        struct GLType<GLEnums::DataType::UnsignedShort>
        {
            typedef unsigned short type;
        };
    }
}

#endif
