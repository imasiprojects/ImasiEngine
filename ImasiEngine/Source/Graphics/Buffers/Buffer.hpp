#ifndef IMASIENGINE_BUFFER_HPP
#define IMASIENGINE_BUFFER_HPP

#include <iostream>
#include <list>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "../Opengl/GLObject.hpp"
#include "BufferAttribute.hpp"
#include "../../Exceptions/InvalidArgumentException.hpp"

namespace ImasiEngine
{
    class Buffer : public GLObject
    {
    private:

        void* _data;
        unsigned int _glBufferType;
        unsigned int _glComponentType;
        unsigned int _componentSize;
        unsigned int _componentCount;
        unsigned int _componentMemberCount;
        unsigned int _componentMemberSize;
        std::list<BufferAttribute> _attributes;

    protected:

        template <
            typename T,
            typename = typename std::enable_if <
                std::is_same<T, float>::value
                || std::is_same<T, double>::value
                || std::is_same<T, int>::value
                || std::is_same<T, unsigned int>::value
                || std::is_same<T, short>::value
                || std::is_same<T, unsigned short>::value
            >::type
        >
        Buffer(unsigned int glBufferType, T* data, unsigned int componentCount, unsigned int componentMemberCount)
            : GLObject()
            , _data(data)
            , _glBufferType(glBufferType)
            , _componentCount(componentCount)
            , _componentMemberCount(componentMemberCount)
        {
            if (_componentMemberCount < 1)
            {
                throw InvalidArgumentException("componentMemberCount", "Must be 1 or more");
            }

            Buffer::createGLObject();

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

            _componentMemberSize = sizeof(T);
            _componentSize = _componentMemberSize * _componentMemberCount;

            createAttributes();
        }

        template <
            typename T,
            typename = typename std::enable_if <
            std::is_same<T, glm::vec2>::value
            || std::is_same<T, glm::vec3>::value
            || std::is_same<T, glm::vec4>::value
            || std::is_same<T, glm::mat2>::value
            || std::is_same<T, glm::mat3>::value
            || std::is_same<T, glm::mat4>::value
            >::type
        >
        Buffer(unsigned int glBufferType, T* data, unsigned int componentCount)
            : GLObject()
            , _data(data)
            , _glBufferType(glBufferType)
            , _componentCount(componentCount)
        {
            Buffer::createGLObject();

            if (std::is_same<T, glm::vec2>())
            {
                _componentMemberCount = 2;
            }
            else if (std::is_same<T, glm::vec3>())
            {
                _componentMemberCount = 3;
            }
            else if (std::is_same<T, glm::vec4>())
            {
                _componentMemberCount = 4;
            }
            else if (std::is_same<T, glm::mat2>())
            {
                _componentMemberCount = 4;
            }
            else if (std::is_same<T, glm::mat3>())
            {
                _componentMemberCount = 9;
            }
            else if (std::is_same<T, glm::mat4>())
            {
                _componentMemberCount = 16;
            }

            _glComponentType = GL_FLOAT;
            _componentMemberSize = sizeof(float);
            _componentSize = _componentMemberSize * _componentMemberCount;

            createAttributes();
        }

        void createGLObject() override;
        void destroyGLObject() override;

        void initBufferData(unsigned int drawMode = GL_STATIC_DRAW) const;
        void createAttributes();

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
