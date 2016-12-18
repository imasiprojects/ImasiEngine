#ifndef IMASIENGINE_GLBUFFERTYPE_HPP
#define IMASIENGINE_GLBUFFERTYPE_HPP

#include <GL/glew.h>

namespace ImasiEngine
{
    namespace Enums
    {
        enum GLBufferType : GLenum
        {
            ArrayBuffer = GL_ARRAY_BUFFER,
            IndexBuffer = GL_ELEMENT_ARRAY_BUFFER
        };

        /*// Must be moved to another file (EnumHelper?)
        template <
            typename T,
            typename = typename std::enable_if<std::is_enum<T>::value>::type,
            typename R = typename std::underlying_type<T>::type
        >
            R getEnumValue(T e)
        {
            return static_cast<R>(e);
        }*/
    }
}

#endif
