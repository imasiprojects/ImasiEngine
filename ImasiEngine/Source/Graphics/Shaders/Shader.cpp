#include "Shader.hpp"

#include "../../Utils/Opengl.hpp"
#include "../../Utils/Logger.hpp"

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

        if (result == GL_FALSE)
        {
            #ifdef DEBUG
            {
                int errorLength;
                glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &errorLength);
                std::string errorMessage(errorLength, '\0');
                glGetShaderInfoLog(shaderId, errorLength, nullptr, &errorMessage[0]);
                Logger::out << "Shader id " << shaderId << " error: " << std::endl << '\t' << errorMessage.c_str() << std::endl;
            }
            #endif

            return false;
        }

        _id = shaderId;
        return true;
    }

    unsigned int Shader::getId() const
    {
        return _id;
    }

}
