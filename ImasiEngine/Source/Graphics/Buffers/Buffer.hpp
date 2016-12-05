#ifndef IMASIENGINE_BUFFER_HPP
#define IMASIENGINE_BUFFER_HPP

#include <iostream>
#include <list>
#include <glm/glm.hpp>

#include "../Opengl/GLObject.hpp"
#include "BufferAttribute.hpp"

namespace ImasiEngine
{
    class Buffer : public GLObject
    {
    private:

        unsigned int _glBufferType;
        unsigned int _glComponentType;
        unsigned int _componentSize;
        unsigned int _componentCount;
        unsigned int _membersPerComponent;
        std::list<BufferAttribute> _attributes;

        void initBufferData(unsigned int glComponentType, unsigned int componentTypeSize, void* data);

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
        void initBufferData(glm::vec2* data);
        void initBufferData(glm::vec3* data);
        void initBufferData(glm::vec4* data);

    public:

        Buffer(const Buffer&) = delete;
        Buffer(Buffer&& buffer) noexcept;
        virtual ~Buffer();

        unsigned int getGLComponentType() const;
        unsigned int getComponentCount() const;
        unsigned int getComponentSize() const;
        const std::list<BufferAttribute>& getAttributes() const;
    };
}

#endif
