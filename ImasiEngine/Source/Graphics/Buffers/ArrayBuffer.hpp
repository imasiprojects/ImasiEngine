#ifndef IMASIENGINE_ARRAYBUFFER_HPP
#define IMASIENGINE_ARRAYBUFFER_HPP

#include <GL/glew.h>

#include "Buffer.hpp"
#include "../Opengl/OpenglHelper.hpp"

namespace ImasiEngine
{
    class ArrayBuffer : public Buffer
    {
    private:

        static const unsigned int _glBufferType = GL_ARRAY_BUFFER;

    public:

        static void bind(ArrayBuffer* buffer);
        static void unbind();

        template<
            typename T,
            typename = typename std::enable_if<
                std::is_same<T, float>::value
                || std::is_same<T, double>::value
                || std::is_same<T, int>::value
                || std::is_same<T, unsigned int>::value
                || std::is_same<T, short>::value
                || std::is_same<T, unsigned short>::value
            >::type
        >
        ArrayBuffer(T* data, unsigned int componentCount, unsigned int componentMemberCount)
            : Buffer(_glBufferType, data, componentCount, componentMemberCount)
        {
            BIND(ArrayBuffer, this);
            {
                initBufferData();
            }
            UNBIND(ArrayBuffer);
        }

        template<
            typename T,
            typename = typename std::enable_if<
                std::is_same<T, glm::vec2>::value
                || std::is_same<T, glm::vec3>::value
                || std::is_same<T, glm::vec4>::value
                || std::is_same<T, glm::mat2>::value
                || std::is_same<T, glm::mat3>::value
                || std::is_same<T, glm::mat4>::value
            >::type
        >
        ArrayBuffer(T* data, unsigned int componentCount)
            : Buffer(_glBufferType, data, componentCount)
        {
            BIND(ArrayBuffer, this);
            {
                initBufferData();
            }
            UNBIND(ArrayBuffer);
        }

        ArrayBuffer(const ArrayBuffer&) = delete;
        ArrayBuffer(ArrayBuffer&& buffer) noexcept;
        virtual ~ArrayBuffer();
    };
}

#endif
