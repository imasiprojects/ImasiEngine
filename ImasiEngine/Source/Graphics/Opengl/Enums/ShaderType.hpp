#ifndef IMASIENGINE_GLSHADERTYPE_HPP
#define IMASIENGINE_GLSHADERTYPE_HPP

#include <GL/glew.h>

namespace ImasiEngine
{
    namespace GLEnums
    {
        enum ShaderType : GLenum
        {
            Vertex = GL_VERTEX_SHADER,
            Fragment = GL_FRAGMENT_SHADER,
        };
    }
}

#endif
