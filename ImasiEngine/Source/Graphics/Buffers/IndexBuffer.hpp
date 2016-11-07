#pragma once

#include <GL/glew.h>

#include "Buffer.hpp"

namespace ImasiEngine
{
    class IndexBuffer : public Buffer
    {
    public:

        static void bind(IndexBuffer* buffer);
        static void unbind();

        template<typename T,
            typename = typename std::enable_if<
                std::is_same<unsigned int, T>::value
                || std::is_same<unsigned short, T>::value
            >::type
        >
        IndexBuffer(T* data, unsigned int componentCount, unsigned int membersPerComponent)
            : Buffer(GL_ELEMENT_ARRAY_BUFFER, componentCount, membersPerComponent)
        {
            IndexBuffer::bind(this);
            {
                initBufferData(data);
            }
            IndexBuffer::unbind();
        }

        IndexBuffer(const IndexBuffer&) = delete;
        IndexBuffer(IndexBuffer&& buffer) noexcept;
        virtual ~IndexBuffer();
    };
}
