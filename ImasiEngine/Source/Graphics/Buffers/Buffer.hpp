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

    protected:

        Buffer();

    public:

        Buffer(const Buffer&) = delete;
        Buffer(Buffer&& buffer) noexcept;
        virtual ~Buffer();

        void initBufferData(float* data, unsigned int componentCount, unsigned int membersPerComponent);
        void initBufferData(double* data, unsigned int componentCount, unsigned int membersPerComponent);
        void initBufferData(int* data, unsigned int componentCount, unsigned int membersPerComponent);
        void initBufferData(unsigned int* data, unsigned int componentCount, unsigned int membersPerComponent);
        void initBufferData(short* data, unsigned int componentCount, unsigned int membersPerComponent);
        void initBufferData(unsigned short* data, unsigned int componentCount, unsigned int membersPerComponent);

        void createGLObject() override;
        void destroyGLObject() override;

        void bind() const;
        void unbind() const;

        virtual unsigned int getGLBufferType() const = 0;
        virtual unsigned int getGLComponentType() const;

        unsigned int getComponentCount() const;
        unsigned int getMembersPerComponent() const;
    };
}
