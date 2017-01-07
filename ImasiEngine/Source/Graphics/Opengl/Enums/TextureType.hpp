#ifndef IMASIENGINE_GLTEXTURETYPE_HPP
#define IMASIENGINE_GLTEXTURETYPE_HPP

#include <GL/glew.h>

namespace ImasiEngine
{
    namespace GLEnums
    {
        enum TextureType : GLenum
        {
            Texture2D = GL_TEXTURE_2D,
            CubeMap = GL_TEXTURE_CUBE_MAP,
        };
    }
}

#endif
