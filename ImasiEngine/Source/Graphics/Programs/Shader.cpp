#include "Shader.hpp"

#include <map>
#include <GL/glew.h>

#include "../Opengl/OpenglHelper.hpp"
#include "../../Utils/Logger.hpp"

namespace ImasiEngine
{
    Shader::Shader()
        : GLObject()
    {
    }

    Shader::Shader(Shader&& shader) noexcept
        : GLObject(std::move(shader))
    {
    }

    Shader::~Shader()
    {
        if (Shader::isValidGLObject())
        {
            Shader::destroyGLObject();
        }
    }

    void Shader::createGLObject()
    {
        unsigned int id = GL(glCreateShader(getGLShaderType()));
        setGLObjectId(id);
    }

    void Shader::destroyGLObject()
    {
        GL(glDeleteShader(getGLObjectId()));
        unsetGLObjectId();
    }

    bool Shader::compile(const char* sourceCode)
    {
        if (Shader::isValidGLObject())
        {
            destroyGLObject();
        }

        createGLObject();
        unsigned int shaderId = getGLObjectId();
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

            destroyGLObject();
        }

        #ifdef DEBUG
        {
            static std::map<unsigned int, std::string> shaderNames
            {
                { GL_VERTEX_SHADER, "Vertex" },
                { GL_FRAGMENT_SHADER, "Fragment" }
            };

            Logger::out << shaderNames[getGLShaderType()] << " shader: " << (compilationSuccess ? "OK" : "ERROR") << std::endl;
        }
        #endif

        return compilationSuccess == GL_TRUE;
    }
}
