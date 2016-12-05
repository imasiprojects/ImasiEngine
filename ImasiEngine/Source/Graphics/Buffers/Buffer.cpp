#include "Buffer.hpp"

#include <GL/glew.h>

#include "../Opengl/OpenglHelper.hpp"

namespace ImasiEngine
{
    void Buffer::initBufferData(unsigned int componentGLType, unsigned int componentTypeSize, void* data)
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

    void Buffer::initBufferData(glm::vec2* data)
    {
        _membersPerComponent = 2;
        initBufferData((float*)data);
    }

    void Buffer::initBufferData(glm::vec3* data)
    {
        _membersPerComponent = 3;
        initBufferData((float*)data);
    }

    void Buffer::initBufferData(glm::vec4* data)
    {
        _membersPerComponent = 4;
        initBufferData((float*)data);
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
