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
                GL(glUniform1d(uniformLocation, *reinterpret_cast<double*>(&value)));
            }
            else if (std::is_same<float, T>::value)
            {
                GL(glUniform1f(uniformLocation, *reinterpret_cast<float*>(&value)));
            }
            else if (std::is_same<int, T>::value)
            {
                GL(glUniform1i(uniformLocation, *reinterpret_cast<int*>(&value)));
            }
            else if (std::is_same<unsigned int, T>::value)
            {
                GL(glUniform1ui(uniformLocation, *reinterpret_cast<unsigned int*>(&value)));
            }
            else if (std::is_same<glm::vec2, T>::value)
            {
                const glm::vec2& vec = *reinterpret_cast<glm::vec2*>(&value);
                GL(glUniform2f(uniformLocation, vec.x, vec.y));
            }
            else if (std::is_same<glm::vec3, T>::value)
            {
                const glm::vec3& vec = *reinterpret_cast<glm::vec3*>(&value);
                GL(glUniform3f(uniformLocation, vec.x, vec.y, vec.z));
            }
            else if (std::is_same<glm::vec4, T>::value)
            {
                const glm::vec4& vec = *reinterpret_cast<glm::vec4*>(&value);
                GL(glUniform4f(uniformLocation, vec.x, vec.y, vec.z, vec.w));
            }
        }
    };
}

#endif
