#ifndef IMASIENGINE_GLBUFFERTYPE_HPP
#define IMASIENGINE_GLBUFFERTYPE_HPP

#include <GL/glew.h>

namespace ImasiEngine
{
    namespace GLEnums
    {
        enum BufferType : GLenum
        {
            ArrayBuffer = GL_ARRAY_BUFFER,
            IndexBuffer = GL_ELEMENT_ARRAY_BUFFER
        };
    }
}

#endif
