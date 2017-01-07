#ifndef IMASIENGINE_GLTYPE_HPP
#define IMASIENGINE_GLTYPE_HPP

#include <GL/glew.h>

namespace ImasiEngine
{
    namespace GLEnums
    {
        enum DataType : GLenum
        {
            Unknown = 0,

            Float = GL_FLOAT,
            Double = GL_DOUBLE,
            Int = GL_INT,
            UnsignedInt = GL_UNSIGNED_INT,
            Short = GL_SHORT,
            UnsignedShort = GL_UNSIGNED_SHORT,
        };
    }
}

#endif
