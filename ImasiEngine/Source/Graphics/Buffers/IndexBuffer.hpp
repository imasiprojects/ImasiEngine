#ifndef IMASIENGINE_INDEXBUFFER_HPP
#define IMASIENGINE_INDEXBUFFER_HPP

#include <GL/glew.h>

#include "Buffer.hpp"
#include "../Opengl/OpenglHelper.hpp"

namespace ImasiEngine
{
    class IndexBuffer : public Buffer
    {
    private:

        static const unsigned int _glBufferType = GL_ELEMENT_ARRAY_BUFFER;

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
        IndexBuffer(T* data, unsigned int componentCount, unsigned int componentMemberCount)
            : Buffer(_glBufferType, data, componentCount, componentMemberCount)
        {
            BIND(IndexBuffer, this);
            {
                initBufferData();
            }
            UNBIND(IndexBuffer);
        }

        IndexBuffer(const IndexBuffer&) = delete;
        IndexBuffer(IndexBuffer&& buffer) noexcept;
        virtual ~IndexBuffer();
    };
}

#endif
