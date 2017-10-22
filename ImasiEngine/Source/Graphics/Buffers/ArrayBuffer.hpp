#ifndef IMASIENGINE_ARRAYBUFFER_HPP
#define IMASIENGINE_ARRAYBUFFER_HPP

#include "Buffer.hpp"

namespace ImasiEngine
{
    class ArrayBuffer
        : public Buffer
    {
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
        ArrayBuffer(T* data, GLsizei componentCount, GLsizei componentMemberCount, GLEnums::BufferUsage bufferUsage = GLEnums::BufferUsage::StaticDraw)
            : Buffer(GLEnums::BufferType::Array, bufferUsage, componentCount, componentMemberCount, data)
        {
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
        ArrayBuffer(T* data, GLsizei componentCount, GLEnums::BufferUsage bufferUsage = GLEnums::BufferUsage::StaticDraw)
            : Buffer(GLEnums::BufferType::Array, bufferUsage, componentCount, data)
        {
        }

        ArrayBuffer(const ArrayBuffer&) = delete;
        ArrayBuffer(ArrayBuffer&& buffer) noexcept;
        virtual ~ArrayBuffer();
    };
}

#endif
