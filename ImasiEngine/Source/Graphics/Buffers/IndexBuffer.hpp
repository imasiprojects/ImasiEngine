#pragma once

#include "Buffer.hpp"

namespace ImasiEngine
{
    class IndexBuffer : public Buffer
    {
    protected:

        unsigned getGLBufferType() const override;

    public:

        IndexBuffer(unsigned int* data, unsigned int componentCount, unsigned int membersPerComponent);
        IndexBuffer(const IndexBuffer&) = delete;
        IndexBuffer(IndexBuffer&& buffer) noexcept;
        virtual ~IndexBuffer();
    };
}
