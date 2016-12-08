#include "Buffer.hpp"

#include "../Opengl/OpenglHelper.hpp"

namespace ImasiEngine
{
    Buffer::Buffer(Buffer&& buffer) noexcept
        : GLObject(std::move(buffer))
        , _data(buffer._data)
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

    void Buffer::initBufferData(unsigned int drawMode) const
    {
        GL(glBufferData(_glBufferType, _componentSize * _componentCount, _data, drawMode));
    }

    void Buffer::createAttributes()
    {
        static int maxComponentMemberCount = 4;
        int componentMemberCount = _componentMemberCount;
        unsigned short offset = 0;

        while (componentMemberCount > 0)
        {
            BufferAttribute attribute;
            attribute.memberCount = std::min(componentMemberCount, maxComponentMemberCount);
            attribute.offset = offset;

            _attributes.push_back(attribute);

            offset += _componentMemberSize * attribute.memberCount;
            componentMemberCount -= maxComponentMemberCount;
        }
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

    const std::list<BufferAttribute>& Buffer::getAttributes() const
    {
        return _attributes;
    }
}