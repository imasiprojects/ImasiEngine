#include "Buffer.hpp"

#include <algorithm>
#include <GL/glew.h>

#include "../../Utils/Opengl.hpp"

namespace ImasiEngine
{
    Buffer::Buffer(float* data, unsigned int componentCount, unsigned int membersPerComponent)
        : GLObject()
        , _glComponentType(GL_FLOAT)
        , _componentCount(componentCount)
        , _membersPerComponent(membersPerComponent)
    {
        Buffer::createGLObject();

        bind();
        GL(glBufferData(Buffer::getGLBufferType(), _componentCount * _membersPerComponent * sizeof(float), data, GL_STATIC_DRAW));
        unbind();
    }

    Buffer::Buffer(double* data, unsigned int componentCount, unsigned int membersPerComponent)
        : GLObject()
        , _glComponentType(GL_DOUBLE)
        , _componentCount(componentCount)
        , _membersPerComponent(membersPerComponent)
    {
        Buffer::createGLObject();

        bind();
        GL(glBufferData(Buffer::getGLBufferType(), _componentCount * _membersPerComponent * sizeof(double), data, GL_STATIC_DRAW));
        unbind();
    }

    Buffer::Buffer(int* data, unsigned int componentCount, unsigned int membersPerComponent)
        : GLObject()
        , _glComponentType(GL_INT)
        , _componentCount(componentCount)
        , _membersPerComponent(membersPerComponent)
    {
        Buffer::createGLObject();

        bind();
        GL(glBufferData(Buffer::getGLBufferType(), _componentCount * _membersPerComponent * sizeof(int), data, GL_STATIC_DRAW));
        unbind();
    }

    Buffer::Buffer(unsigned int* data, unsigned int componentCount, unsigned int membersPerComponent)
        : GLObject()
        , _glComponentType(GL_UNSIGNED_INT)
        , _componentCount(componentCount)
        , _membersPerComponent(membersPerComponent)
    {
        Buffer::createGLObject();

        bind();
        GL(glBufferData(Buffer::getGLBufferType(), _componentCount * _membersPerComponent * sizeof(unsigned int), data, GL_STATIC_DRAW));
        unbind();
    }

    Buffer::Buffer(short* data, unsigned int componentCount, unsigned int membersPerComponent)
        : GLObject()
        , _glComponentType(GL_SHORT)
        , _componentCount(componentCount)
        , _membersPerComponent(membersPerComponent)
    {
        Buffer::createGLObject();

        bind();
        GL(glBufferData(Buffer::getGLBufferType(), _componentCount * _membersPerComponent * sizeof(short), data, GL_STATIC_DRAW));
        unbind();
    }

    Buffer::Buffer(unsigned short* data, unsigned int componentCount, unsigned int membersPerComponent)
        : GLObject()
        , _glComponentType(GL_UNSIGNED_SHORT)
        , _componentCount(componentCount)
        , _membersPerComponent(membersPerComponent)
    {
        Buffer::createGLObject();

        bind();
        GL(glBufferData(Buffer::getGLBufferType(), _componentCount * _membersPerComponent * sizeof(unsigned short), data, GL_STATIC_DRAW));
        unbind();
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

    unsigned Buffer::getGLBufferType() const
    {
        return GL_ARRAY_BUFFER;
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
