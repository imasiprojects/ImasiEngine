#pragma once

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
        void checkOpenglError(const char* file, const int line, const char* call = nullptr);
    }
}
