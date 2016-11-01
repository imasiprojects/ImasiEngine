#include "Shader.hpp"

#include "../../Utils/Opengl.hpp"

namespace ImasiEngine
{
    Shader::Shader()
        : _id(UNSET)
    {

    }

    Shader::Shader(Shader&& shader) noexcept
    {
        _id = shader._id;
        shader._id = UNSET;
    }

    Shader::~Shader()
    {
        if (_id != UNSET)
        {
            GL(glDeleteShader(_id));
        }
    }

    bool Shader::compile(const char* shaderSourceCode, GLenum type)
    {

        if (_id != UNSET)
        {
            GL(glDeleteShader(_id));
            _id = UNSET;
        }

        unsigned int shaderId = GL(glCreateShader(type));

        GL(glShaderSource(shaderId, 1, &shaderSourceCode, nullptr));
        GL(glCompileShader(shaderId));

        int result = GL_FALSE;

        GL(glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result));

        if (result == GL_TRUE)
        {
            _id = shaderId;

            return true;
        }

        return false;

    }

    unsigned int Shader::getId() const
    {
        return _id;
    }

}
