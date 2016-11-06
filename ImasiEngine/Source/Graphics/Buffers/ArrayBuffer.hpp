#pragma once

#include "Buffer.hpp"

namespace ImasiEngine
{
    class ArrayBuffer : public Buffer
    {
    public:

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
            : Buffer(componentCount, membersPerComponent)
        {
            initBufferData(data);
        }

        ArrayBuffer(const ArrayBuffer&) = delete;
        ArrayBuffer(ArrayBuffer&& buffer) noexcept;
        virtual ~ArrayBuffer();

        unsigned int getGLBufferType() const override;
    };
}
