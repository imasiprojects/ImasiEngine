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
        unsigned int _componentMemberSize;
        std::list<BufferAttribute> _attributes;

    protected:

        Buffer(unsigned int glBufferType, unsigned int componentCount, unsigned int componentMemberCount = 0);

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
                _componentMemberSize = sizeof(float);
            }
            else if (std::is_same<T, double>())
            {
                _glComponentType = GL_DOUBLE;
                _componentMemberSize = sizeof(double);
            }
            else if (std::is_same<T, int>())
            {
                _glComponentType = GL_INT;
                _componentMemberSize = sizeof(int);
            }
            else if (std::is_same<T, unsigned int>())
            {
                _glComponentType = GL_UNSIGNED_INT;
                _componentMemberSize = sizeof(unsigned int);
            }
            else if (std::is_same<T, short>())
            {
                _glComponentType = GL_SHORT;
                _componentMemberSize = sizeof(short);
            }
            else if (std::is_same<T, unsigned short>())
            {
                _glComponentType = GL_UNSIGNED_SHORT;
                _componentMemberSize = sizeof(unsigned short);
            }
            else if (std::is_same<T, glm::vec2>())
            {
                _glComponentType = GL_FLOAT;
                _componentMemberSize = sizeof(float);
                _componentMemberCount = 2;
            }
            else if (std::is_same<T, glm::vec3>())
            {
                _glComponentType = GL_FLOAT;
                _componentMemberSize = sizeof(float);
                _componentMemberCount = 3;
            }
            else if (std::is_same<T, glm::vec4>())
            {
                _glComponentType = GL_FLOAT;
                _componentMemberSize = sizeof(float);
                _componentMemberCount = 4;
            }
            else if (std::is_same<T, glm::mat2>())
            {
                _glComponentType = GL_FLOAT;
                _componentMemberSize = sizeof(float);
                _componentMemberCount = 4;
            }
            else if (std::is_same<T, glm::mat3>())
            {
                _glComponentType = GL_FLOAT;
                _componentMemberSize = sizeof(float);
                _componentMemberCount = 9;
            }
            else if (std::is_same<T, glm::mat4>())
            {
                _glComponentType = GL_FLOAT;
                _componentMemberSize = sizeof(float);
                _componentMemberCount = 16;
            }
            else
            {
                throw "Invalid component type";
            }

            _componentSize = _componentMemberSize * _componentMemberCount;
            GL(glBufferData(_glBufferType, _componentSize * _componentCount, data, GL_STATIC_DRAW));

            // Create Attributes

            static int maxComponentMemberCount = 4;
            int componentMemberCount = _componentMemberCount;
            int offset = 0;

            while (componentMemberCount > 0)
            {
                BufferAttribute attribute;
                attribute.memberCount = std::min(componentMemberCount, maxComponentMemberCount);
                attribute.offset = offset;

                _attributes.push_back(attribute);

                offset += _componentMemberSize * attribute.memberCount;
                componentMemberCount -= maxComponentMemberCount;
            }
        }

    public:

        Buffer(const Buffer&) = delete;
        Buffer(Buffer&& buffer) noexcept;
        virtual ~Buffer();

        unsigned int getGLComponentType() const;
        unsigned int getComponentCount() const;
        unsigned int getComponentSize() const;
        unsigned int getComponentMemberCount() const;
        const std::list<BufferAttribute>& getAttributes() const;
    };
}

#endif
