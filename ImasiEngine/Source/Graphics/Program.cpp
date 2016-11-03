#include "Program.hpp"

#include <GL/glew.h>

#include "../Utils/Opengl.hpp"
#include "../Utils/Logger.hpp"

namespace ImasiEngine
{
    void Program::bind(Program* program)
    {
        GL(glUseProgram(program->getGpuId()));
    }

    void Program::unbind()
    {
        GL(glUseProgram(UNBIND));
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
        setGpuId(id);
    }

    void Program::destroyGpuObject()
    {
        GL(glDeleteProgram(getGpuId()));
        unsetGpuId();
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
            if (shader.isValidGpuId())
            {
                GL(glAttachShader(getGpuId(), shader.getGpuId()));
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
            GL(glDetachShader(getGpuId(), shader.getGpuId()));
        }
    }

    bool Program::link()
    {
        unsigned int gpuId = getGpuId();

        if (_isLinked)
        {
            Logger::out << "Program id " << gpuId << ": This Program has been linked yet" << std::endl;
            return false;
        }

        if (_invalidAttachPerformed)
        {
            Logger::out << "Program id " << gpuId << ": An attach of an invalid shader was performed" << std::endl;
            return false;
        }

        int linkSuccess = GL_FALSE;

        GL(glLinkProgram(gpuId));
        GL(glGetProgramiv(gpuId, GL_LINK_STATUS, &linkSuccess));

        if (linkSuccess == GL_FALSE)
        {
            #ifdef DEBUG
            {
                int errorLength;
                GL(glGetProgramiv(gpuId, GL_INFO_LOG_LENGTH, &errorLength));
                std::string errorMessage(errorLength, '\0');
                GL(glGetProgramInfoLog(gpuId, errorLength, nullptr, &errorMessage[0]));
                Logger::out << "Program id " << gpuId << " error: " << std::endl << errorMessage.c_str() << std::endl;
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
