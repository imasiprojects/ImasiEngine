#include "ArrayBuffer.hpp"

#include <algorithm>
#include <GL/glew.h>

namespace ImasiEngine
{
    ArrayBuffer::ArrayBuffer(float* data, unsigned int componentCount, unsigned int membersPerComponent)
        : Buffer(componentCount, membersPerComponent)
    {
        initBufferData(data);
    }

    ArrayBuffer::ArrayBuffer(double* data, unsigned int componentCount, unsigned int membersPerComponent)
        : Buffer(componentCount, membersPerComponent)
    {
        initBufferData(data);
    }

    ArrayBuffer::ArrayBuffer(int* data, unsigned int componentCount, unsigned int membersPerComponent)
        : Buffer(componentCount, membersPerComponent)
    {
        initBufferData(data);
    }

    ArrayBuffer::ArrayBuffer(unsigned int* data, unsigned int componentCount, unsigned int membersPerComponent)
        : Buffer(componentCount, membersPerComponent)
    {
        initBufferData(data);
    }

    ArrayBuffer::ArrayBuffer(short* data, unsigned int componentCount, unsigned int membersPerComponent)
        : Buffer(componentCount, membersPerComponent)
    {
        initBufferData(data);
    }

    ArrayBuffer::ArrayBuffer(unsigned short* data, unsigned int componentCount, unsigned int membersPerComponent)
        : Buffer(componentCount, membersPerComponent)
    {
        initBufferData(data);
    }

    ArrayBuffer::ArrayBuffer(ArrayBuffer&& buffer) noexcept
        : Buffer(std::move(buffer))
    {
    }

    ArrayBuffer::~ArrayBuffer()
    {
    }

    unsigned int ArrayBuffer::getGLBufferType() const
    {
        return GL_ARRAY_BUFFER;
    }
}
