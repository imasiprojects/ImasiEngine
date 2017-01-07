#ifndef IMASIENGINE_GLBUFFERTYPE_HPP
#define IMASIENGINE_GLBUFFERTYPE_HPP

#include <GL/glew.h>

namespace ImasiEngine
{
    namespace GLEnums
    {
        enum BufferType : GLenum
        {
            Array = GL_ARRAY_BUFFER,
            Index = GL_ELEMENT_ARRAY_BUFFER,
            CopyRead = GL_COPY_READ_BUFFER,
            CopyWrite = GL_COPY_WRITE_BUFFER,
        };
    }
}

#endif
