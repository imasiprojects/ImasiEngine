#include "IndexBuffer.hpp"

#include <GL/glew.h>

#include "../../Utils/Opengl.hpp"

namespace ImasiEngine
{
    void IndexBuffer::bind(IndexBuffer* buffer)
    {
        GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->getGLObjectId()));
    }

    void IndexBuffer::unbind()
    {
        GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL_ID));
    }

    IndexBuffer::IndexBuffer(IndexBuffer&& buffer) noexcept
        : Buffer(std::move(buffer))
    {
    }

    IndexBuffer::~IndexBuffer()
    {
    }
}
