#include <iostream>
#include <GL/glew.h>

#include "Shader.hpp"
#include "../../Utils/Logger.hpp"
#include "../../Utils/Opengl.hpp"

namespace ImasiEngine
{
    void Shader::bind(Shader* shader)
    {
        GL(glUseProgram(shader->_id));
    }

    void Shader::unbind()
    {
        GL(glUseProgram(UNBIND));
    }

    Shader::Shader()
    {
        _id = 0;
    }

    Shader::~Shader()
    {
        GL(glDeleteProgram(_id));
    }

    bool Shader::loadFromStrings(const char* vertexShader, const char* fragmentShader)
    {
        unsigned int programId = glCreateProgram();
        unsigned int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        unsigned int fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

        int result = GL_FALSE;

        // Compile vertex Shader
        glShaderSource(vertexShaderId, 1, &vertexShader, nullptr);
        glCompileShader(vertexShaderId);

        #ifdef DEBUG
        {
            glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &result);
            Logger::out << "Vertex shader: " << (result ? "OK" : "ERROR") << std::endl;
        }
        #endif

        // Compile fragment Shader
        glShaderSource(fragmentShaderId, 1, &fragmentShader, nullptr);
        glCompileShader(fragmentShaderId);

        #ifdef DEBUG
        {
            glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &result);
            Logger::out << "Fragment shader: " << (result ? "OK" : "ERROR") << std::endl;
        }
        #endif

        // Link both shaders
        glAttachShader(programId, vertexShaderId);
        glAttachShader(programId, fragmentShaderId);
        glLinkProgram(programId);

        // Clean memory
        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);

        glGetProgramiv(programId, GL_LINK_STATUS, &result);

        if (result)
        {
            _id = programId;
        }
        else
        {
            #ifdef DEBUG
            {
                int errorLength;
                glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &errorLength);
                std::string errorMessage(errorLength, 1);
                glGetProgramInfoLog(programId, errorLength, nullptr, &errorMessage[0]);
                Logger::out << "Shader id " << programId << " error: " << std::endl << '\t' << errorMessage.c_str() << std::endl;
            }
            #endif

            glDeleteProgram(programId);
        }

        return result == GL_TRUE;
    }
}
