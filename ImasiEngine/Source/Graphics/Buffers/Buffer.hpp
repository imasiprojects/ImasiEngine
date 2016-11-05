#pragma once

#include "../GLObject.hpp"

namespace ImasiEngine
{
    class Buffer : public GLObject
    {
    private:

        unsigned int _glComponentType;
        unsigned int _componentCount;
        unsigned int _membersPerComponent;

    public:

        Buffer(float* data, unsigned int componentCount, unsigned int membersPerComponent);
        Buffer(double* data, unsigned int componentCount, unsigned int membersPerComponent);
        Buffer(int* data, unsigned int componentCount, unsigned int membersPerComponent);
        Buffer(unsigned int* data, unsigned int componentCount, unsigned int membersPerComponent);
        Buffer(short* data, unsigned int componentCount, unsigned int membersPerComponent);
        Buffer(unsigned short* data, unsigned int componentCount, unsigned int membersPerComponent);
        Buffer(const Buffer&) = delete;
        Buffer(Buffer&& buffer) noexcept;
        virtual ~Buffer();

        void createGLObject() override;
        void destroyGLObject() override;

        void bind() const;
        void unbind() const;

        virtual unsigned int getGLBufferType() const;
        virtual unsigned int getGLComponentType() const;

        unsigned int getComponentCount() const;
        unsigned int getMembersPerComponent() const;
    };
}
