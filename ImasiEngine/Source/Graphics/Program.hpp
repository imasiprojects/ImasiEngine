#ifndef IMASIENGINE_PROGRAM_HPP
#define IMASIENGINE_PROGRAM_HPP

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

#include "Shaders/Shader.hpp"
#include "GLObject.hpp"
#include "../Utils/Logger.hpp"
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
            if (!_isLinked)
            {
                Logger::out << "Error: Trying to set uniform on unlinked Program!" << std::endl;
                return;
            }

            int uniformLocation = getUniformLocation(uniform);

            if (std::is_same<double, T>::value)
            {
                GL(glUniform1dv(uniformLocation, 1, reinterpret_cast<double*>(&value)));
            }
            else if (std::is_same<float, T>::value)
            {
                GL(glUniform1fv(uniformLocation, 1, reinterpret_cast<float*>(&value)));
            }
            else if (std::is_same<int, T>::value)
            {
                GL(glUniform1iv(uniformLocation, 1, reinterpret_cast<int*>(&value)));
            }
            else if (std::is_same<unsigned int, T>::value)
            {
                GL(glUniform1uiv(uniformLocation, 1, reinterpret_cast<unsigned int*>(&value)));
            }
            else if (std::is_same<glm::vec2, T>::value)
            {
                GL(glUniform2fv(uniformLocation, 1, glm::value_ptr(*reinterpret_cast<glm::vec2*>(&value))));
            }
            else if (std::is_same<glm::vec3, T>::value)
            {
                GL(glUniform3fv(uniformLocation, 1, glm::value_ptr(*reinterpret_cast<glm::vec3*>(&value))));
            }
            else if (std::is_same<glm::vec4, T>::value)
            {
                GL(glUniform4fv(uniformLocation, 1, glm::value_ptr(*reinterpret_cast<glm::vec4*>(&value))));
            }
            else if (std::is_same<glm::mat4, T>::value)
            {
                GL(glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(*reinterpret_cast<glm::mat4*>(&value))));
            }
        }
    };
}

#endif
