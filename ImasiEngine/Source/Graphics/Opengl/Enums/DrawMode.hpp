#ifndef IMASIENGINE_GLDRAWMODE_HPP
#define IMASIENGINE_GLDRAWMODE_HPP

#include <GL/glew.h>

namespace ImasiEngine
{
    namespace GLEnums
    {
        enum DrawMode : GLenum
        {
            Points = GL_POINTS,
            Lines = GL_LINES,
            LineLoop = GL_LINE_LOOP,
            LineStrip = GL_LINE_STRIP,
            Triangles = GL_TRIANGLES,
            TriangleStrip = GL_TRIANGLE_STRIP,
            Quads = GL_QUADS,
            QuadStrip = GL_QUAD_STRIP,
            Polygon = GL_POLYGON,
        };
    }
}

#endif
