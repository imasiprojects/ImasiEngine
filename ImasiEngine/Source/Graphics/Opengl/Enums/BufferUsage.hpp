#ifndef IMASIENGINE_GLBUFFERUSAGE_HPP
#define IMASIENGINE_GLBUFFERUSAGE_HPP

#include <GL/glew.h>

namespace ImasiEngine
{
    namespace GLEnums
    {
        enum BufferUsage : GLenum
        {
            StaticDraw = GL_STATIC_DRAW,
            DynamicDraw = GL_DYNAMIC_DRAW,
            StreamDraw = GL_STREAM_DRAW,
        };
    }
}

#endif
