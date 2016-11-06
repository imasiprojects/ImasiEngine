#pragma once

#include "Buffer.hpp"

namespace ImasiEngine
{
    class IndexBuffer : public Buffer
    {
    protected:

        unsigned getGLBufferType() const override;

    public:

        template<typename T,
            typename = typename std::enable_if<
                std::is_same<unsigned int, T>::value
                || std::is_same<unsigned short, T>::value
            >::type
        >
        IndexBuffer(T* data, unsigned int componentCount, unsigned int membersPerComponent)
            : Buffer(componentCount, membersPerComponent)
        {
            initBufferData(data);
        }

        IndexBuffer(const IndexBuffer&) = delete;
        IndexBuffer(IndexBuffer&& buffer) noexcept;
        virtual ~IndexBuffer();
    };
}
