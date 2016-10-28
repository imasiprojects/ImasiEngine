#pragma once

#include <GL/glew.h>

#include "Logger.hpp"

#ifdef DEBUG

    #define GL(glCall) do { \
        glCall; \
        ImasiEngine::OpenglDebugger::checkOpenglError(__FILE__, __LINE__, #glCall); \
    } while (false)

    #define GL_CHECK() do { \
        ImasiEngine::OpenglDebugger::checkOpenglError(__FILE__, __LINE__); \
    } while (false)

#else

    #define GL(glCall) glCall

    #define GL_CHECK() 

#endif

namespace ImasiEngine
{
    namespace OpenglDebugger
    {
        static void checkOpenglError(const char* file, const int line, const char* call = nullptr)
        {
            const GLenum error = glGetError();
            if (error != GL_NO_ERROR)
            {
                const unsigned char* description = glewGetErrorString(error);
                if (call != nullptr)
                {
                    Logger::out << "OpenGL error " << error << " `" << description << "` @ " << file << ":" << line << " - `" << call << "`" << std::endl;
                }
                else
                {
                    Logger::out << "OpenGL error " << error << " `" << description << "` @ " << file << ":" << line << std::endl;
                }
            }
        }
    };
}
