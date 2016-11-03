#include "GLObject.hpp"

#include "../Utils/Opengl.hpp"

namespace ImasiEngine
{
    GLObject::GLObject()
        : _glId(NULL_ID)
    {
    }

    GLObject::GLObject(GLObject&& glObject) noexcept
        : _glId(glObject._glId)
    {
        glObject.unsetGLObjectId();
    }

    GLObject::~GLObject()
    {
    }

    void GLObject::setGLObjectId(unsigned int id)
    {
        _glId = id;
    }

    void GLObject::unsetGLObjectId()
    {
        _glId = NULL_ID;
    }

    void GLObject::resetGLObject()
    {
        if (isValidGLObject())
        {
            destroyGLObject();
        }

        createGLObject();
    }

    unsigned int GLObject::getGLObjectId() const
    {
        return _glId;
    }

    bool GLObject::isValidGLObject() const
    {
        return _glId != NULL_ID;
    }
}
