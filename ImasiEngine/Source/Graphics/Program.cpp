#include "Program.hpp"

#include <GL/glew.h>

#include "../Utils/Opengl.hpp"
#include "../Utils/Logger.hpp"

namespace ImasiEngine
{
    void Program::bind(Program* program)
    {
        GL(glUseProgram(program->getGpuObjectId()));
    }

    void Program::unbind()
    {
        GL(glUseProgram(NULL_ID));
    }

    Program::Program()
        : GpuObject()
        , _isLinked(false)
        , _invalidAttachPerformed(false)
    {
        Program::createGpuObject();
    }

    Program::Program(Program&& program) noexcept
        : GpuObject(std::move(program))
        , _isLinked(program._isLinked)
        , _invalidAttachPerformed(program._invalidAttachPerformed)
    {
    }

    Program::~Program()
    {
        Program::destroyGpuObject();
    }

    void Program::createGpuObject()
    {
        unsigned int id = GL(glCreateProgram());
        setGpuObjectId(id);
    }

    void Program::destroyGpuObject()
    {
        GL(glDeleteProgram(getGpuObjectId()));
        unsetGpuObjectId();
    }

    bool Program::isLinked() const
    {
        return _isLinked;
    }

    bool Program::invalidAttachPerformed() const
    {
        return _invalidAttachPerformed;
    }

    void Program::attach(const Shader& shader)
    {
        if (!_isLinked && !_invalidAttachPerformed)
        {
            if (shader.isValidGpuObject())
            {
                GL(glAttachShader(getGpuObjectId(), shader.getGpuObjectId()));
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
            GL(glDetachShader(getGpuObjectId(), shader.getGpuObjectId()));
        }
    }

    bool Program::link()
    {
        unsigned int id = getGpuObjectId();

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
        resetGpuObject();

        _isLinked = false;
        _invalidAttachPerformed = false;
    }
}
