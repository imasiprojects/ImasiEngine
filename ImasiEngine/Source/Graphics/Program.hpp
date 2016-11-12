#ifndef IMASIENGINE_PROGRAM_HPP
#define IMASIENGINE_PROGRAM_HPP

#include <iostream>

#include "Shaders/Shader.hpp"
#include "GLObject.hpp"

#include <glm/glm.hpp>
#include "../Utils/Logger.hpp"
#include <GL/glew.h>
#include "../Utils/Opengl.hpp"

namespace ImasiEngine
{
    class Program : public GLObject
    {
    private:

        bool _isLinked;
        bool _invalidAttachPerformed;

    protected:

        void createGLObject() override;
        void destroyGLObject() override;

    public:

        static void bind(Program* program);
        static void unbind();

        Program();
        Program(const Program&) = delete;
        Program(Program&& program) noexcept;
        virtual ~Program();

        bool isLinked() const;

        void attach(const Shader& shader);
        void detach(const Shader& shader);
        bool link();

        void reset();

        int getUniformLocation(char* uniform) const;

        template<typename T,
            typename = typename std::enable_if<
                std::is_same<double, T>::value
                || std::is_same<float, T>::value
                || std::is_same<int, T>::value
                || std::is_same<unsigned int, T>::value
                || std::is_same<glm::vec2, T>::value
                || std::is_same<glm::vec3, T>::value
                || std::is_same<glm::vec4, T>::value
                || std::is_same<glm::mat4, T>::value
            >::type
        >
        void setUniform(char* uniform, T value)
        {
            int uniformLocation = getUniformLocation(uniform);

            if (std::is_same<double, T>::value)
            {
                GL(glUniform1d(uniformLocation, value));
            }
            else if (std::is_same<float, T>::value)
            {
                GL(glUniform1f(uniformLocation, value));
            }
            else if (std::is_same<int, T>::value)
            {
                GL(glUniform1i(uniformLocation, value));
            }
            else if (std::is_same<unsigned int, T>::value)
            {
                GL(glUniform1ui(uniformLocation, value));
            }
            else if (std::is_same<glm::vec2, T>::value)
            {
                GL(glUniform2d(uniformLocation, ((glm::vec2)value).x, ((glm::vec2)value).y));
            }
            else if (std::is_same<glm::vec3, T>::value)
            {
                GL(glUniform3d(uniformLocation, ((glm::vec3)value).x, ((glm::vec3)value).y, ((glm::vec3)value).z));
            }
            else if (std::is_same<glm::vec4, T>::value)
            {
                GL(glUniform4d(uniformLocation, ((glm::vec4)value).x, ((glm::vec4)value).y, ((glm::vec4)value).z, ((glm::vec4)value).w));
            }
        }
    };
}

#endif
