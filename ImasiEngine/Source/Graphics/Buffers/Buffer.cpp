#include "Buffer.hpp"

#include <GL/glew.h>

#include "../Opengl/OpenglHelper.hpp"

namespace ImasiEngine
{
    Buffer::Buffer(unsigned int glBufferType, unsigned int componentCount, unsigned int componentMemberCount)
        : GLObject()
        , _glBufferType(glBufferType)
        , _componentCount(componentCount)
        , _componentMemberCount(componentMemberCount)
    {
        if (_componentMemberCount < 1)
        {
            // Fatal error, not valid componentMemberCount
        }

        Buffer::createGLObject();
    }

    Buffer::Buffer(Buffer&& buffer) noexcept
        : GLObject(std::move(buffer))
        , _glBufferType(buffer._glBufferType)
        , _glComponentType(buffer._glComponentType)
        , _componentSize(buffer._componentSize)
        , _componentCount(buffer._componentCount)
        , _componentMemberCount(buffer._componentMemberCount)
        , _componentMemberSize(buffer._componentMemberSize)
        , _attributes(buffer._attributes)
    {
    }

    Buffer::~Buffer()
    {
        Buffer::destroyGLObject();
    }

    unsigned int Buffer::getGLComponentType() const
    {
        return _glComponentType;
    }

    unsigned int Buffer::getComponentCount() const
    {
        return _componentCount;
    }

    unsigned int Buffer::getComponentSize() const
    {
        return _componentSize;
    }

    unsigned int Buffer::getComponentMemberCount() const
    {
        return _componentMemberCount;
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

    const std::list<BufferAttribute>& Buffer::getAttributes() const
    {
        return _attributes;
    }
}
