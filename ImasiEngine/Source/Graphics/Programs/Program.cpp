#include "Program.hpp"

#include <GL/glew.h>

#include "../Opengl/OpenglHelper.hpp"
#include "../../Utils/Logger.hpp"

namespace ImasiEngine
{
    void Program::bind(Program* program)
    {
        GL(glUseProgram(program->getGLObjectId()));
    }

    void Program::unbind()
    {
        GL(glUseProgram(NULL_ID));
    }

    Program::Program()
        : GLObject()
        , _isLinked(false)
        , _invalidAttachPerformed(false)
    {
        Program::createGLObject();
    }

    Program::Program(Program&& program) noexcept
        : GLObject(std::move(program))
        , _isLinked(program._isLinked)
        , _invalidAttachPerformed(program._invalidAttachPerformed)
    {
    }

    Program::~Program()
    {
        Program::destroyGLObject();
    }

    void Program::createGLObject()
    {
        unsigned int id = GL(glCreateProgram());
        setGLObjectId(id);
    }

    void Program::destroyGLObject()
    {
        GL(glDeleteProgram(getGLObjectId()));
        unsetGLObjectId();
    }

    bool Program::isLinked() const
    {
        return _isLinked;
    }

    void Program::attach(const Shader& shader)
    {
        if (!_isLinked && !_invalidAttachPerformed)
        {
            if (shader.isValidGLObject())
            {
                GL(glAttachShader(getGLObjectId(), shader.getGLObjectId()));
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
            GL(glDetachShader(getGLObjectId(), shader.getGLObjectId()));
        }
    }

    bool Program::link()
    {
        unsigned int id = getGLObjectId();

        if (_isLinked)
        {
            Logger::out << "Program id " << id << ": This Program has been linked yet" << std::endl;
            return false;
        }

        if (_invalidAttachPerformed)
        {
            Logger::out << "Program id " << id << ": An attach of an invalid shader was performed" << std::endl;
            return false;
        }

        int linkSuccess = GL_FALSE;

        GL(glLinkProgram(id));
        GL(glGetProgramiv(id, GL_LINK_STATUS, &linkSuccess));

        if (linkSuccess == GL_FALSE)
        {
            #ifdef DEBUG
            {
                int errorLength;
                GL(glGetProgramiv(id, GL_INFO_LOG_LENGTH, &errorLength));
                std::string errorMessage(errorLength, '\0');
                GL(glGetProgramInfoLog(id, errorLength, nullptr, &errorMessage[0]));
                Logger::out << "Program id " << id << " error: " << std::endl << errorMessage.c_str() << std::endl;
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
        resetGLObject();

        _isLinked = false;
        _invalidAttachPerformed = false;
    }

    int Program::getUniformLocation(char* uniform) const
    {
        return glGetUniformLocation(getGLObjectId(), uniform);
    }
}
