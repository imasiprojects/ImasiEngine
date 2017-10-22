#ifndef IMASIENGINE_BUFFER_HPP
#define IMASIENGINE_BUFFER_HPP

#include <iostream>
#include <list>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "../Opengl/OpenglHelper.hpp"
#include "../Opengl/GLObject.hpp"
#include "../Opengl/Enums/BufferType.hpp"
#include "BufferAttribute.hpp"
#include "../../Exceptions/InvalidArgumentException.hpp"
#include "../Opengl/Enums/BufferUsage.hpp"
#include "../Opengl/Enums/DataType.hpp"

namespace ImasiEngine
{
    class Buffer
        : public GLObject
    {
    private:

        GLEnums::BufferType _glBufferType;
        GLEnums::DataType _glComponentType;
        GLsizei _componentSize;
        GLsizei _componentCount;
        GLsizei _componentMemberCount;
        GLsizei _componentMemberSize;
        GLEnums::BufferUsage _bufferUsage;
        std::list<BufferAttribute> _attributes;

        Buffer(const Buffer& buffer);
        Buffer(const Buffer& buffer, GLEnums::BufferUsage bufferUsage);

    protected:

        template <
            typename T,
            typename = typename std::enable_if<
                std::is_same<T, float>::value
                || std::is_same<T, double>::value
                || std::is_same<T, int>::value
                || std::is_same<T, unsigned int>::value
                || std::is_same<T, short>::value
                || std::is_same<T, unsigned short>::value
            >::type
        >
        Buffer(GLEnums::BufferType glBufferType, GLEnums::BufferUsage bufferUsage, GLsizei componentCount, GLsizei componentMemberCount, T* data)
            : GLObject()
            , _glBufferType(glBufferType)
            , _componentCount(componentCount)
            , _componentMemberCount(componentMemberCount)
            , _bufferUsage(bufferUsage)
        {
            if (_componentMemberCount < 1)
            {
                throw InvalidArgumentException("componentMemberCount", "Must be 1 or more");
            }

            Buffer::createGLObject();

            _glComponentType = OpenglHelper::getGLType<T>();

            _componentMemberSize = sizeof(T);
            _componentSize = _componentMemberSize * _componentMemberCount;

            createAttributes();

            GL(glBindBuffer(_glBufferType, getGLObjectId()));
            GL(glBufferData(_glBufferType, _componentSize * _componentCount, data, _bufferUsage));
            GL(glBindBuffer(_glBufferType, NULL_ID));
        }

        template <
            typename T,
            typename = typename std::enable_if<
                std::is_same<T, glm::vec2>::value
                || std::is_same<T, glm::vec3>::value
                || std::is_same<T, glm::vec4>::value
                || std::is_same<T, glm::mat2>::value
                || std::is_same<T, glm::mat3>::value
                || std::is_same<T, glm::mat4>::value
            >::type
        >
        Buffer(GLEnums::BufferType glBufferType, GLEnums::BufferUsage bufferUsage, GLsizei componentCount, T* data)
            : GLObject()
            , _glBufferType(glBufferType)
            , _componentCount(componentCount)
            , _bufferUsage(bufferUsage)
        {
            Buffer::createGLObject();

            if (std::is_same<T, glm::vec2>::value)
            {
                _componentMemberCount = 2;
            }
            else if (std::is_same<T, glm::vec3>::value)
            {
                _componentMemberCount = 3;
            }
            else if (std::is_same<T, glm::vec4>::value)
            {
                _componentMemberCount = 4;
            }
            else if (std::is_same<T, glm::mat2>::value)
            {
                _componentMemberCount = 4;
            }
            else if (std::is_same<T, glm::mat3>::value)
            {
                _componentMemberCount = 9;
            }
            else if (std::is_same<T, glm::mat4>::value)
            {
                _componentMemberCount = 16;
            }

            _glComponentType = GLEnums::DataType::Float;
            _componentMemberSize = sizeof(float);
            _componentSize = _componentMemberSize * _componentMemberCount;

            createAttributes();

            GL(glBindBuffer(_glBufferType, getGLObjectId()));
            GL(glBufferData(_glBufferType, _componentSize * _componentCount, data, _bufferUsage));
            GL(glBindBuffer(_glBufferType, NULL_ID));
        }

        void createGLObject() override;
        void destroyGLObject() override;

        void createAttributes();

    public:

        Buffer(Buffer&& buffer) noexcept;
        virtual ~Buffer();

        template <
            typename T,
            typename = typename std::enable_if<
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
        void update(GLsizei componentOffset, GLsizei componentCount, T* data)
        {
            if (OpenglHelper::getGLType<T>() != _glComponentType)
            {
                throw InvalidArgumentException("data", "Data type must be the same as the data of the buffer");
            }

            if (std::is_same<T, glm::vec2>::value && _componentMemberCount != 2
                || std::is_same<T, glm::vec3>::value && _componentMemberCount != 3
                || std::is_same<T, glm::vec4>::value && _componentMemberCount != 4
                || std::is_same<T, glm::mat2>::value && _componentMemberCount != 4
                || std::is_same<T, glm::mat3>::value && _componentMemberCount != 9
                || std::is_same<T, glm::mat4>::value && _componentMemberCount != 16)
            {
                throw InvalidArgumentException("data", "Invalid members per component");
            }

            if (componentOffset >= _componentCount)
            {
                throw InvalidArgumentException("offset", "Out of range");
            }

            GL(glBindBuffer(_glBufferType, getGLObjectId()));
            GL(glBufferSubData(_glBufferType, componentOffset * _componentSize, componentCount * _componentSize, data));
            GL(glBindBuffer(_glBufferType, NULL_ID));
        }

        void read(GLsizei componentOffset, GLsizei componentCount, void* outData) const;
        void copyFrom(const Buffer* buffer, GLsizei componentOffset, GLsizei componentOffsetFrom, GLsizei componentCount);
        void resize(GLsizei componentCount);

        Buffer clone() const;
        Buffer clone(GLEnums::BufferUsage bufferUsage) const;

        GLenum getGLComponentType() const;
        GLsizei getComponentCount() const;
        GLsizei getComponentSize() const;
        GLsizei getComponentMemberCount() const;
        GLsizei getBufferUsage() const;
        const std::list<BufferAttribute>& getAttributes() const;
    };
}

#endif
