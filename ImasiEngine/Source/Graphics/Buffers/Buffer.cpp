#include "Buffer.hpp"

#include <GL/glew.h>

#include "../../Utils/Opengl.hpp"

namespace ImasiEngine
{
    void Buffer::initBufferData(unsigned int componentGLType, std::size_t componentTypeSize, void* data)
    {
        _glComponentType = componentGLType;

        bind();
        GL(glBufferData(getGLBufferType(), _componentCount * _membersPerComponent * componentTypeSize, data, GL_STATIC_DRAW));
        unbind();
    }

    Buffer::Buffer(unsigned int componentCount, unsigned int membersPerComponent)
        : GLObject()
        , _componentCount(componentCount)
        , _membersPerComponent(membersPerComponent)
    {
        Buffer::createGLObject();
    }

    Buffer::Buffer(Buffer&& buffer) noexcept
        : GLObject(std::move(buffer))
        , _glComponentType(buffer._glComponentType)
        , _componentCount(buffer._componentCount)
        , _membersPerComponent(buffer._membersPerComponent)
    {
    }

    Buffer::~Buffer()
    {
        Buffer::destroyGLObject();
    }

    void Buffer::initBufferData(float* data)
    {
        initBufferData(GL_FLOAT, sizeof(float), data);
    }

    void Buffer::initBufferData(double* data)
    {
        initBufferData(GL_DOUBLE, sizeof(double), data);
    }

    void Buffer::initBufferData(int* data)
    {
        initBufferData(GL_INT, sizeof(int), data);
    }

    void Buffer::initBufferData(unsigned int* data)
    {
        initBufferData(GL_UNSIGNED_INT, sizeof(unsigned int), data);
    }

    void Buffer::initBufferData(short* data)
    {
        initBufferData(GL_SHORT, sizeof(short), data);
    }

    void Buffer::initBufferData(unsigned short* data)
    {
        initBufferData(GL_UNSIGNED_SHORT, sizeof(unsigned short), data);
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

    void Buffer::bind() const
    {
        GL(glBindBuffer(getGLBufferType(), getGLObjectId()));
    }

    void Buffer::unbind() const
    {
        GL(glBindBuffer(getGLBufferType(), NULL_ID));
    }

    unsigned Buffer::getGLComponentType() const
    {
        return _glComponentType;
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
