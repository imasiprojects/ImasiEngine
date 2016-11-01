#include "Program.hpp"

#include <GL/glew.h>

#include "../Utils/Opengl.hpp"
#include "../Utils/Logger.hpp"

namespace ImasiEngine
{

    Program::Program()
        : _id(UNSET),
        _isLinked(false)
    {
        _id = glCreateProgram();
    }

    Program::Program(Program&& program) noexcept
    {
        _id = program._id;
        program._id = UNSET;

        _isLinked = program._isLinked;
        program._isLinked = false;
    }

    Program::~Program()
    {
        if (_id != UNSET)
        {
            GL(glDeleteProgram(_id));
        }
    }

    void Program::attach(const Shader& shader)
    {
        if (!_isLinked)
        {
            GL(glAttachShader(_id, shader.getId()));
        }
    }

    void Program::detach(const Shader& shader)
    {
        if (!_isLinked)
        {
            GL(glDetachShader(_id, shader.getId()));
        }
    }

    bool Program::link()
    {
        if (_isLinked)
        {
            return false;
        }

        int result;

        glLinkProgram(_id);

        glGetProgramiv(_id, GL_LINK_STATUS, &result);

        if (result == GL_FALSE)
        {
            #ifdef DEBUG
            {
                int errorLength;
                glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &errorLength);
                std::string errorMessage(errorLength, '\0');
                glGetProgramInfoLog(_id, errorLength, nullptr, &errorMessage[0]);
                Logger::out << "Shader id " << _id << " error: " << std::endl << '\t' << errorMessage.c_str() << std::endl;
            }
            #endif

            glDeleteProgram(_id);
            _id = glCreateProgram();

            return false;
        }

        _isLinked = true;
        return true;
    }

    unsigned int Program::getId() const
    {
        return _id;
    }

    bool Program::isLinked() const
    {
        return _isLinked;
    }

    void Program::bind(Program* program)
    {
        GL(glUseProgram(program->getId()));
    }

    void Program::unbind()
    {
        GL(glUseProgram(UNBIND));
    }
}
