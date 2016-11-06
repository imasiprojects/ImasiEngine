#pragma once

#include "Buffer.hpp"

namespace ImasiEngine
{
    class ArrayBuffer : public Buffer
    {
    public:

        template<class T>
        ArrayBuffer(T* data, unsigned int componentCount, unsigned int membersPerComponent)
            : Buffer(componentCount, membersPerComponent)
        {
            initBufferData(data);
        }

        ArrayBuffer(const ArrayBuffer&) = delete;
        ArrayBuffer(ArrayBuffer&& buffer) noexcept;
        virtual ~ArrayBuffer();

        unsigned int getGLBufferType() const override;
    };
}
