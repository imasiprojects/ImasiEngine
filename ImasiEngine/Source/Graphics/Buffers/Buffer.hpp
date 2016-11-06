#pragma once

#include <iostream>

#include "../GLObject.hpp"

namespace ImasiEngine
{
    class Buffer : public GLObject
    {
    private:

        unsigned int _glComponentType;
        unsigned int _componentCount;
        unsigned int _membersPerComponent;

        void initBufferData(unsigned int bufferGLType, unsigned int componentGLType, std::size_t componentTypeSize, void* data);

    protected:

        Buffer(unsigned int componentCount, unsigned int membersPerComponent);

        void initBufferData(unsigned int bufferGLType, float* data);
        void initBufferData(unsigned int bufferGLType, double* data);
        void initBufferData(unsigned int bufferGLType, int* data);
        void initBufferData(unsigned int bufferGLType, unsigned int* data);
        void initBufferData(unsigned int bufferGLType, short* data);
        void initBufferData(unsigned int bufferGLType, unsigned short* data);

    public:

        Buffer(const Buffer&) = delete;
        Buffer(Buffer&& buffer) noexcept;
        virtual ~Buffer();

        void createGLObject() override;
        void destroyGLObject() override;

        virtual unsigned int getGLComponentType() const;

        unsigned int getComponentCount() const;
        unsigned int getMembersPerComponent() const;
    };
}
