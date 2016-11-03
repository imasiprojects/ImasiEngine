#pragma once

#include "../GLObject.hpp"

namespace ImasiEngine
{
    class Buffer : public GLObject
    {
    private:

        unsigned int _componentCount;
        unsigned int _membersPerComponent;

    public:

        static void bind(Buffer* buffer);
        static void unbind();

        Buffer(float* data, unsigned int componentCount, unsigned int membersPerComponent);
        Buffer(const Buffer&) = delete;
        Buffer(Buffer&& buffer) noexcept;
        virtual ~Buffer();

        void createGLObject() override;
        void destroyGLObject() override;

        unsigned int getComponentCount() const;
        unsigned int getMembersPerComponent() const;
    };
}
