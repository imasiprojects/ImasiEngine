#ifndef IMASIENGINE_INDEXBUFFER_HPP
#define IMASIENGINE_INDEXBUFFER_HPP

#include "Buffer.hpp"

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
        IndexBuffer(T* data, unsigned int componentCount, unsigned int componentMemberCount, GLEnums::BufferUsage bufferUsage = GLEnums::StaticDraw)
            : Buffer(GLEnums::BufferType::IndexBuffer, bufferUsage, componentCount, componentMemberCount, data)
        {
        }

        IndexBuffer(const IndexBuffer&) = delete;
        IndexBuffer(IndexBuffer&& buffer) noexcept;
        virtual ~IndexBuffer();
    };
}

#endif
