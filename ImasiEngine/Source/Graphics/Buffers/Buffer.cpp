#include <GL/glew.h>

#include "Buffer.hpp"
#include "../../Utils/Opengl.hpp"

namespace ImasiEngine
{
    void Buffer::bind(Buffer* buffer)
    {
        GL(glBindBuffer(GL_ARRAY_BUFFER, buffer->_id));
    }

    void Buffer::unbind()
    {
        GL(glBindBuffer(GL_ARRAY_BUFFER, UNBIND));
    }

    Buffer::Buffer(float* data, unsigned int componentCount, unsigned int membersPerComponent)
        : GpuObject()
        , _componentCount(componentCount)
        , _membersPerComponent(membersPerComponent)
    {
        GL(glGenBuffers(1, &_id));

        Buffer::bind(this);
        GL(glBufferData(GL_ARRAY_BUFFER, componentCount * membersPerComponent * sizeof(float), data, GL_STATIC_DRAW));
        Buffer::unbind();
    }

    Buffer::~Buffer()
    {
        GL(glDeleteBuffers(1, &_id));
    }

    unsigned int Buffer::getComponentCount() const
    {
        return _componentCount;
    }

    unsigned int Buffer::getMembersPerComponent() const
    {
        return _membersPerComponent;
    }
}
