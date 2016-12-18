#ifndef IMASIENGINE_INDEXBUFFER_HPP
#define IMASIENGINE_INDEXBUFFER_HPP

#include <GL/glew.h>

#include "Buffer.hpp"
#include "../Opengl/Types/glBufferType.hpp"

namespace ImasiEngine
{
    class IndexBuffer
        : public Buffer
    {
    public:

        static void bind(IndexBuffer* buffer);
        static void unbind();

        template<
            typename T,
            typename = typename std::enable_if<
                std::is_same<unsigned int, T>::value
                || std::is_same<unsigned short, T>::value
            >::type
        >
        IndexBuffer(T* data, unsigned int componentCount, unsigned int componentMemberCount, unsigned int bufferUsage = GL_STATIC_DRAW)
            : Buffer(GLBufferType::IndexBuffer, bufferUsage, componentCount, componentMemberCount, data)
        {
        }

        IndexBuffer(const IndexBuffer&) = delete;
        IndexBuffer(IndexBuffer&& buffer) noexcept;
        virtual ~IndexBuffer();
    };
}

#endif
