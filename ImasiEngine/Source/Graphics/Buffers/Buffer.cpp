#include "Buffer.hpp"

#include "../Opengl/OpenglHelper.hpp"

namespace ImasiEngine
{
    Buffer::Buffer(Buffer&& buffer) noexcept
        : GLObject(std::move(buffer))
        , _glBufferType(buffer._glBufferType)
        , _glComponentType(buffer._glComponentType)
        , _componentSize(buffer._componentSize)
        , _componentCount(buffer._componentCount)
        , _componentMemberCount(buffer._componentMemberCount)
        , _componentMemberSize(buffer._componentMemberSize)
        , _bufferUsage(buffer._bufferUsage)
        , _attributes(std::move(buffer._attributes))
    {
    }
    
    Buffer::Buffer(const Buffer& buffer)
        : Buffer(buffer, buffer._bufferUsage)
    {
    }

    Buffer::Buffer(const Buffer& buffer, unsigned int bufferUsage)
        : GLObject()
        , _glBufferType(buffer._glBufferType)
        , _glComponentType(buffer._glComponentType)
        , _componentSize(buffer._componentSize)
        , _componentCount(buffer._componentCount)
        , _componentMemberCount(buffer._componentMemberCount)
        , _componentMemberSize(buffer._componentMemberSize)
        , _bufferUsage(bufferUsage)
        , _attributes(buffer._attributes)
    {
        Buffer::createGLObject();

        GL(glBindBuffer(_glBufferType, getGLObjectId()));
        GL(glBufferData(_glBufferType, _componentSize * _componentCount, nullptr, _bufferUsage));
        copyFrom(&buffer, 0, 0, _componentCount);
        GL(glBindBuffer(_glBufferType, NULL_ID));
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

    void Buffer::createAttributes()
    {
        static const int maxComponentMemberCount = 4;
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

    void Buffer::copyFrom(const Buffer* buffer, unsigned int componentOffset, unsigned int componentOffsetFrom, unsigned int componentCount)
    {
        if (_glComponentType != buffer->getGLComponentType())
        {
            throw InvalidArgumentException("buffer", "Different types");
        }
        if (_componentMemberCount != buffer->getComponentMemberCount())
        {
            throw InvalidArgumentException("buffer", "Different members per component");
        }
        if (componentOffset >= _componentCount)
        {
            throw InvalidArgumentException("componentOffset", "Out of range");
        }
        if (componentOffsetFrom >= buffer->getComponentCount())
        {
            throw InvalidArgumentException("componentOffsetFrom", "Out of range");
        }
        if (componentCount + componentOffset > _componentCount)
        {
            throw InvalidArgumentException("componentCount", "Out of range (this buffer)");
        }
        if (componentCount + componentOffsetFrom > buffer->getComponentCount())
        {
            throw InvalidArgumentException("componentCount", "Out of range ('from' buffer)");
        }

        GL(glBindBuffer(GL_COPY_READ_BUFFER, buffer->getGLObjectId()));
        GL(glBindBuffer(GL_COPY_WRITE_BUFFER, getGLObjectId()));

        GL(glCopyBufferSubData(
            GL_COPY_READ_BUFFER,
            GL_COPY_WRITE_BUFFER,
            componentOffsetFrom * _componentSize,
            componentOffset * _componentSize,
            componentCount * _componentSize
        ));

        GL(glBindBuffer(GL_COPY_READ_BUFFER, NULL_ID));
        GL(glBindBuffer(GL_COPY_WRITE_BUFFER, NULL_ID));
    }

    void Buffer::read(unsigned int componentOffset, unsigned int componentCount, void* outData) const
    {
        if (componentOffset >= _componentCount)
        {
            throw InvalidArgumentException("componentOffset", "Out of range");
        }
        if (componentCount + componentOffset > _componentCount)
        {
            throw InvalidArgumentException("componentCount", "Out of range");
        }

        GL(glBindBuffer(_glBufferType, getGLObjectId()));

        glGetBufferSubData(
            _glBufferType,
            componentOffset * _componentSize,
            componentCount * _componentSize,
            outData
        );

        GL(glBindBuffer(_glBufferType, NULL_ID));
    }

    void Buffer::resize(unsigned int componentCount)
    {
        unsigned int minComponentCount = std::min(_componentCount, componentCount);

        _componentCount = minComponentCount;

        Buffer temp(*this);

        _componentCount = componentCount;

        GL(glBindBuffer(_glBufferType, getGLObjectId()));
        GL(glBufferData(_glBufferType, _componentSize * componentCount, nullptr, _bufferUsage));
        GL(glBindBuffer(_glBufferType, NULL_ID));

        copyFrom(&temp, 0, 0, minComponentCount);
    }

    Buffer Buffer::clone() const
    {
        return Buffer(*this);
    }

    Buffer Buffer::clone(unsigned int bufferUsage) const
    {
        return Buffer(*this, bufferUsage);
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

    unsigned int Buffer::getBufferUsage() const
    {
        return _bufferUsage;
    }

    const std::list<BufferAttribute>& Buffer::getAttributes() const
    {
        return _attributes;
    }
}