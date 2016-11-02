#pragma once

#include "../GpuObject.hpp"

namespace ImasiEngine
{
    class Buffer : public GpuObject
    {
    private:

        unsigned int _componentCount;
        unsigned int _membersPerComponent;

    public:

        static void bind(Buffer* buffer);
        static void unbind();

        Buffer(float* data, unsigned int componentCount, unsigned int membersPerComponent);
        ~Buffer();

        unsigned int getComponentCount() const;
        unsigned int getMembersPerComponent() const;
    };
}
