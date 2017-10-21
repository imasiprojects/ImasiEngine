#include "IndexBuffer.hpp"

#include <GL/glew.h>

#include "../Opengl/OpenglHelper.hpp"

namespace ImasiEngine
{
    void IndexBuffer::bind(const IndexBuffer& buffer)
    {
        GL(glBindBuffer(GLEnums::BufferType::Index, buffer.getGLObjectId()));
    }

    void IndexBuffer::unbind()
    {
        GL(glBindBuffer(GLEnums::BufferType::Index, NULL_ID));
    }

    IndexBuffer::IndexBuffer(IndexBuffer&& buffer) noexcept
        : Buffer(std::move(buffer))
    {
    }

    IndexBuffer::~IndexBuffer()
    {
    }
}
