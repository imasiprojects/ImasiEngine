#include <GL/glew.h>

#include "Buffer.hpp"
#include "../../Utils/Opengl.hpp"

namespace ImasiEngine
{
    void Buffer::bind(Buffer* buffer)
    {
        GL(glBindBuffer(GL_ARRAY_BUFFER, buffer->getGLObjectId()));
    }

    void Buffer::unbind()
    {
        GL(glBindBuffer(GL_ARRAY_BUFFER, NULL_ID));
    }

    Buffer::Buffer(float* data, unsigned int componentCount, unsigned int membersPerComponent)
        : GLObject()
        , _componentCount(componentCount)
        , _membersPerComponent(membersPerComponent)
    {
        Buffer::createGLObject();

        Buffer::bind(this);
        GL(glBufferData(GL_ARRAY_BUFFER, componentCount * membersPerComponent * sizeof(float), data, GL_STATIC_DRAW));
        Buffer::unbind();
    }

    Buffer::Buffer(Buffer&& buffer) noexcept
        : GLObject(std::move(buffer))
        , _componentCount(buffer._componentCount)
        , _membersPerComponent(buffer._membersPerComponent)
    {
    }

    Buffer::~Buffer()
    {
        Buffer::destroyGLObject();
    }

    void Buffer::createGLObject()
    {
        unsigned int id;
        GL(glGenBuffers(1, &id));

        setGLObjectId(id);
    }

    void Buffer::destroyGLObject()
    {
        unsigned int id = getGLObjectId();
        GL(glDeleteBuffers(1, &id));

        unsetGLObjectId();
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
