#include "Opengl.hpp"

#include <GL/glew.h>

#include "Logger.hpp"

namespace ImasiEngine
{
    namespace Opengl
    {
        void beginSfml(sf::RenderWindow* window)
        {
            window->pushGLStates();
        }

        void endSfml(sf::RenderWindow* window)
        {
            window->popGLStates();
        }

        void checkError(const char* file, const int line, const char* call)
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
    }
}
