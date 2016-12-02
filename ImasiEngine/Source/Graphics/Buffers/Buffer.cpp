#include "Buffer.hpp"

#include <GL/glew.h>

#include "../Opengl/OpenglHelper.hpp"

namespace ImasiEngine
{
    void Buffer::initBufferData(unsigned int componentGLType, std::size_t componentTypeSize, void* data)
    {
        _glComponentType = componentGLType;
        GL(glBufferData(_glBufferType, _componentCount * _membersPerComponent * componentTypeSize, data, GL_STATIC_DRAW));
    }

    Buffer::Buffer(unsigned int glBufferType, unsigned int componentCount, unsigned int membersPerComponent)
        : GLObject()
        , _glBufferType(glBufferType)
        , _componentCount(componentCount)
        , _membersPerComponent(membersPerComponent)
    {
        Buffer::createGLObject();
    }

    Buffer::Buffer(Buffer&& buffer) noexcept
        : GLObject(std::move(buffer))
        , _glBufferType(buffer._glBufferType)
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

    unsigned int Buffer::getGLBufferType() const
    {
        return _glBufferType;
    }

    unsigned int Buffer::getGLComponentType() const
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
