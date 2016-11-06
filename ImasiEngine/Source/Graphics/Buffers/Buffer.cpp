#include "Buffer.hpp"

#include <GL/glew.h>

#include "../../Utils/Opengl.hpp"

namespace ImasiEngine
{
    void Buffer::initBufferData(unsigned int bufferGLType, unsigned int componentGLType, std::size_t componentTypeSize, void* data)
    {
        _glComponentType = componentGLType;
        GL(glBufferData(bufferGLType, _componentCount * _membersPerComponent * componentTypeSize, data, GL_STATIC_DRAW));
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

    void Buffer::initBufferData(unsigned int bufferGLType, float* data)
    {
        initBufferData(bufferGLType, GL_FLOAT, sizeof(float), data);
    }

    void Buffer::initBufferData(unsigned int bufferGLType, double* data)
    {
        initBufferData(bufferGLType, GL_DOUBLE, sizeof(double), data);
    }

    void Buffer::initBufferData(unsigned int bufferGLType, int* data)
    {
        initBufferData(bufferGLType, GL_INT, sizeof(int), data);
    }

    void Buffer::initBufferData(unsigned int bufferGLType, unsigned int* data)
    {
        initBufferData(bufferGLType, GL_UNSIGNED_INT, sizeof(unsigned int), data);
    }

    void Buffer::initBufferData(unsigned int bufferGLType, short* data)
    {
        initBufferData(bufferGLType, GL_SHORT, sizeof(short), data);
    }

    void Buffer::initBufferData(unsigned int bufferGLType, unsigned short* data)
    {
        initBufferData(bufferGLType, GL_UNSIGNED_SHORT, sizeof(unsigned short), data);
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
