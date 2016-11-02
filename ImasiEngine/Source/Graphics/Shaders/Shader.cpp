#include "Shader.hpp"

#include "../../Utils/Opengl.hpp"
#include "../../Utils/Logger.hpp"

namespace ImasiEngine
{
    Shader::Shader()
        : GpuObject()
    {
    }

    Shader::Shader(Shader&& shader) noexcept
        : GpuObject(std::move(shader))
    {
        _id = shader._id;
        shader._id = UNSET;
    }

    Shader::~Shader()
    {
        if (GpuObject::isValid())
        {
            GL(glDeleteShader(_id));
        }
    }

    bool Shader::compile(const char* sourceCode, GLenum type)
    {
        if (GpuObject::isValid())
        {
            GL(glDeleteShader(_id));
            _id = UNSET;
        }

        unsigned int shaderId = GL(glCreateShader(type));
        int compilationSuccess = GL_FALSE;

        GL(glShaderSource(shaderId, 1, &sourceCode, nullptr));
        GL(glCompileShader(shaderId));
        GL(glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compilationSuccess));

        if (compilationSuccess == GL_FALSE)
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
}
