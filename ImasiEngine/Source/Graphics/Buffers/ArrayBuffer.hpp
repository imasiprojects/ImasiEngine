#ifndef IMASIENGINE_ARRAYBUFFER_HPP
#define IMASIENGINE_ARRAYBUFFER_HPP

#include <GL/glew.h>

#include "Buffer.hpp"
#include "../../Utils/Opengl.hpp"

namespace ImasiEngine
{
    class ArrayBuffer : public Buffer
    {
    public:

        static void bind(ArrayBuffer* buffer);
        static void unbind();

        template<typename T,
            typename = typename std::enable_if<
                std::is_same<float, T>::value
                || std::is_same<double, T>::value
                || std::is_same<int, T>::value
                || std::is_same<unsigned int, T>::value
                || std::is_same<short, T>::value
                || std::is_same<unsigned short, T>::value
            >::type
        >
        ArrayBuffer(T* data, unsigned int componentCount, unsigned int membersPerComponent)
            : Buffer(GL_ARRAY_BUFFER, componentCount, membersPerComponent)
        {
            BIND(ArrayBuffer, this);
            {
                initBufferData(data);
            }
            UNBIND(ArrayBuffer);
        }

        ArrayBuffer(const ArrayBuffer&) = delete;
        ArrayBuffer(ArrayBuffer&& buffer) noexcept;
        virtual ~ArrayBuffer();
    };
}

#endif