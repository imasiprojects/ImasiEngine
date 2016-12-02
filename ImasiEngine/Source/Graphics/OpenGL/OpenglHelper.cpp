#include "OpenglHelper.hpp"

#include <GL/glew.h>

#include "../../Utils/Logger.hpp"

namespace ImasiEngine
{
    namespace OpenglHelper
    {
        void beginSfml(sf::RenderWindow* window)
        {
            window->pushGLStates();
        }

        void endSfml(sf::RenderWindow* window)
        {
            window->popGLStates();
        }

        bool checkError(const char* file, const int line, const char* call)
        {
            const GLenum error = glGetError();

            if (error == GL_NO_ERROR)
            {
                return false;
            }

            const unsigned char* description = glewGetErrorString(error);
            if (call != nullptr)
            {
                Logger::out << "OpenGL error " << error << " `" << description << "` @ " << file << ":" << line << " - `" << call << "`" << std::endl;
            }
            else
            {
                Logger::out << "OpenGL error " << error << " `" << description << "` @ " << file << ":" << line << std::endl;
            }

            return true;
        }
    }
}
