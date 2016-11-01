#include "Shader.hpp"

#include "../../Utils/Opengl.hpp"

namespace ImasiEngine
{
    Shader::Shader() : _id(0) {}

    Shader::Shader(Shader&& shader)
    {
        _id = shader._id;
        shader._id = 0;
    }

    Shader::~Shader(){
        if (_id != 0)
        {
            GL(glDeleteShader(_id));
        }
    }

    bool Shader::load(const char* code, GLenum type)
    {

        if (_id != 0)
        {
            GL(glDeleteShader(_id));
            _id = 0;
        }

        unsigned int shaderId = glCreateShader(type);

        GL(glShaderSource(shaderId, 1, &code, nullptr));
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
