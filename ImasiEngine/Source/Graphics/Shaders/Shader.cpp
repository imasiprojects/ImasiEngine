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
    }

    Shader::~Shader()
    {
        if (Shader::isValidGpuId())
        {
            Shader::destroyGpuObject();
        }
    }

    void Shader::createGpuObject()
    {
        unsigned int id = GL(glCreateShader(getShaderType()));
        setGpuId(id);
    }

    void Shader::destroyGpuObject()
    {
        GL(glDeleteShader(getGpuId()));
        unsetGpuId();
    }

    bool Shader::compile(const char* sourceCode)
    {
        if (Shader::isValidGpuId())
        {
            destroyGpuObject();
        }

        createGpuObject();
        unsigned int shaderId = getGpuId();
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
                Logger::out << "Shader id " << shaderId << " error: " << std::endl << errorMessage.c_str() << std::endl;
            }
            #endif

            destroyGpuObject();

            return false;
        }

        return true;
    }
}
