#include "Shader.hpp"

#include <map>
#include <GL/glew.h>

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
        if (Shader::isValidGpuObject())
        {
            Shader::destroyGpuObject();
        }
    }

    void Shader::createGpuObject()
    {
        unsigned int id = GL(glCreateShader(getOpenglShaderType()));
        setGpuObjectId(id);
    }

    void Shader::destroyGpuObject()
    {
        GL(glDeleteShader(getGpuObjectId()));
        unsetGpuObjectId();
    }

    bool Shader::compile(const char* sourceCode)
    {
        static std::map<unsigned int, std::string> shaderNames
        {
            { GL_VERTEX_SHADER, "Vertex" },
            { GL_FRAGMENT_SHADER, "Fragment" }
        };

        if (Shader::isValidGpuObject())
        {
            destroyGpuObject();
        }

        createGpuObject();
        unsigned int shaderId = getGpuObjectId();
        int compilationSuccess = GL_FALSE;

        GL(glShaderSource(shaderId, 1, &sourceCode, nullptr));
        GL(glCompileShader(shaderId));
        GL(glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compilationSuccess));

        if (!compilationSuccess)
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
        }

        #ifdef DEBUG
        {
            Logger::out << shaderNames[getOpenglShaderType()] << " shader: " << (compilationSuccess ? "OK" : "ERROR") << std::endl;
        }
        #endif

        return compilationSuccess == GL_TRUE;
    }
}
