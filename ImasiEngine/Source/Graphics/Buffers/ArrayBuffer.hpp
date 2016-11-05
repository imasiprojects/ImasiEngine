#pragma once

#include "Buffer.hpp"

namespace ImasiEngine
{
    class ArrayBuffer : public Buffer
    {
    public:

        ArrayBuffer(float* data, unsigned int componentCount, unsigned int membersPerComponent);
        ArrayBuffer(double* data, unsigned int componentCount, unsigned int membersPerComponent);
        ArrayBuffer(int* data, unsigned int componentCount, unsigned int membersPerComponent);
        ArrayBuffer(unsigned int* data, unsigned int componentCount, unsigned int membersPerComponent);
        ArrayBuffer(short* data, unsigned int componentCount, unsigned int membersPerComponent);
        ArrayBuffer(unsigned short* data, unsigned int componentCount, unsigned int membersPerComponent);
        ArrayBuffer(const ArrayBuffer&) = delete;
        ArrayBuffer(ArrayBuffer&& buffer) noexcept;
        virtual ~ArrayBuffer();

        unsigned int getGLBufferType() const override;
    };
}
