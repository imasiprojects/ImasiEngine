#include "Program.hpp"

#include <GL/glew.h>

#include "../Utils/Opengl.hpp"
#include "../Utils/Logger.hpp"

namespace ImasiEngine
{
    void Program::bind(Program* program)
    {
        GL(glUseProgram(program->getId()));
    }

    void Program::unbind()
    {
        GL(glUseProgram(UNBIND));
    }

    Program::Program()
        : _id(UNSET)
        , _isLinked(false)
        , _invalidAttachPerformed(false)
    {
        _id = GL(glCreateProgram());
    }

    Program::Program(Program&& program) noexcept
    {
        _id = program._id;
        program._id = UNSET;

        _isLinked = program._isLinked;
        program._isLinked = false;

        _invalidAttachPerformed = program._invalidAttachPerformed;
        program._invalidAttachPerformed = true;
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
        if (!_isLinked && !_invalidAttachPerformed)
        {
            if (shader.isValid())
            {
                GL(glAttachShader(_id, shader.getId()));
            }
            else
            {
                _invalidAttachPerformed = true;
            }
        }
    }

    void Program::detach(const Shader& shader)
    {
        if (!_isLinked && !_invalidAttachPerformed)
        {
            GL(glDetachShader(_id, shader.getId()));
        }
    }

    bool Program::link()
    {
        if (_isLinked)
        {
            Logger::out << "Program id " << _id << ": This Program has been linked yet" << std::endl;
            return false;
        }

        if (_invalidAttachPerformed)
        {
            Logger::out << "Program id " << _id << ": An attach of an invalid shader was performed" << std::endl;
            return false;
        }

        int result;

        GL(glLinkProgram(_id));

        GL(glGetProgramiv(_id, GL_LINK_STATUS, &result));

        if (result == GL_FALSE)
        {
            #ifdef DEBUG
            {
                int errorLength;
                GL(glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &errorLength));
                std::string errorMessage(errorLength, '\0');
                GL(glGetProgramInfoLog(_id, errorLength, nullptr, &errorMessage[0]));
                Logger::out << "Program id " << _id << " error: " << std::endl << '\t' << errorMessage.c_str() << std::endl;
            }
            #endif

            reset();

            return false;
        }

        _isLinked = true;
        return true;
    }

    void Program::reset()
    {
        GL(glDeleteProgram(_id));
        _id = GL(glCreateProgram());
        _isLinked = false;
        _invalidAttachPerformed = false;
    }

    unsigned int Program::getId() const
    {
        return _id;
    }

    bool Program::isLinked() const
    {
        return _isLinked;
    }

    bool Program::invalidAttachPerformed() const
    {
        return _invalidAttachPerformed;
    }
}
