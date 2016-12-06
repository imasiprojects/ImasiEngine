#ifndef IMASIENGINE_BUFFER_HPP
#define IMASIENGINE_BUFFER_HPP

#include <iostream>
#include <list>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "../Opengl/GLObject.hpp"
#include "../Opengl/OpenglHelper.hpp"
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
        unsigned int _componentMemberCount;
        std::list<BufferAttribute> _attributes;

    protected:

        Buffer(unsigned int glBufferType, unsigned int componentCount, unsigned int membersPerComponent = 0);

        void createGLObject() override;
        void destroyGLObject() override;

        template <
            typename T,
            typename = typename std::enable_if <
                std::is_same<T, float>::value
                || std::is_same<T, double>::value
                || std::is_same<T, int>::value
                || std::is_same<T, unsigned int>::value
                || std::is_same<T, short>::value
                || std::is_same<T, unsigned short>::value
                || std::is_same<T, glm::vec2>::value
                || std::is_same<T, glm::vec3>::value
                || std::is_same<T, glm::vec4>::value
                || std::is_same<T, glm::mat2>::value
                || std::is_same<T, glm::mat3>::value
                || std::is_same<T, glm::mat4>::value
            >::type
        >
        void initBufferData(T* data)
        {
            if (std::is_same<T, float>())
            {
                _glComponentType = GL_FLOAT;
            }
            else if (std::is_same<T, double>())
            {
                _glComponentType = GL_DOUBLE;
            }
            else if (std::is_same<T, int>())
            {
                _glComponentType = GL_INT;
            }
            else if (std::is_same<T, unsigned int>())
            {
                _glComponentType = GL_UNSIGNED_INT;
            }
            else if (std::is_same<T, short>())
            {
                _glComponentType = GL_SHORT;
            }
            else if (std::is_same<T, unsigned short>())
            {
                _glComponentType = GL_UNSIGNED_SHORT;
            }
            else if (std::is_same<T, glm::vec2>())
            {
                _glComponentType = GL_FLOAT;
                _componentMemberCount = 2;
            }
            else if (std::is_same<T, glm::vec3>())
            {
                _glComponentType = GL_FLOAT;
                _componentMemberCount = 3;
            }
            else if (std::is_same<T, glm::vec4>())
            {
                _glComponentType = GL_FLOAT;
                _componentMemberCount = 4;
            }
            else if (std::is_same<T, glm::mat2>())
            {
                _glComponentType = GL_FLOAT;
                _componentMemberCount = 4;
            }
            else if (std::is_same<T, glm::mat3>())
            {
                _glComponentType = GL_FLOAT;
                _componentMemberCount = 9;
            }
            else if (std::is_same<T, glm::mat4>())
            {
                _glComponentType = GL_FLOAT;
                _componentMemberCount = 16;
            }
            else
            {
                // Wtf error
            }

            _componentSize = sizeof(T) * _componentMemberCount;
            GL(glBufferData(_glBufferType, _componentCount * _componentSize, data, GL_STATIC_DRAW));

            // Create Attributes
        }

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
