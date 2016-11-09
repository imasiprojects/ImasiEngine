#ifndef IMASIENGINE_BUFFER_HPP
#define IMASIENGINE_BUFFER_HPP

#include <iostream>

#include "../GLObject.hpp"

namespace ImasiEngine
{
    class Buffer : public GLObject
    {
    private:

        unsigned int _glBufferType;
        unsigned int _glComponentType;
        unsigned int _componentCount;
        unsigned int _membersPerComponent;

        void initBufferData(unsigned int glComponentType, std::size_t componentTypeSize, void* data);

    protected:

        Buffer(unsigned int glBufferType, unsigned int componentCount, unsigned int membersPerComponent);

        void createGLObject() override;
        void destroyGLObject() override;

        void initBufferData(float* data);
        void initBufferData(double* data);
        void initBufferData(int* data);
        void initBufferData(unsigned int* data);
        void initBufferData(short* data);
        void initBufferData(unsigned short* data);

    public:

        Buffer(const Buffer&) = delete;
        Buffer(Buffer&& buffer) noexcept;
        virtual ~Buffer();

        unsigned int getGLBufferType() const;
        unsigned int getGLComponentType() const;

        unsigned int getComponentCount() const;
        unsigned int getMembersPerComponent() const;
    };
}

#endif