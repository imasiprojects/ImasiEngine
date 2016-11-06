#pragma once

#include <GL/glew.h>

#include "Buffer.hpp"

namespace ImasiEngine
{
    class ArrayBuffer : public Buffer
    {
    public:

        static void bind(ArrayBuffer* buffer);
        static void unbind();

        template<typename T,
            typename = typename std::enable_if<
                std::is_same<float, T>::value
                || std::is_same<double, T>::value
                || std::is_same<int, T>::value
                || std::is_same<unsigned int, T>::value
                || std::is_same<short, T>::value
                || std::is_same<unsigned short, T>::value
            >::type
        >
        ArrayBuffer(T* data, unsigned int componentCount, unsigned int membersPerComponent)
            : Buffer(componentCount, membersPerComponent)
        {
            ArrayBuffer::bind(this);
            initBufferData(GL_ARRAY_BUFFER, data);
            ArrayBuffer::unbind();
        }

        ArrayBuffer(const ArrayBuffer&) = delete;
        ArrayBuffer(ArrayBuffer&& buffer) noexcept;
        virtual ~ArrayBuffer();
    };
}
