#include "OpenglHelper.hpp"

#include <GL/glew.h>

#include "../../Utils/Logger.hpp"
#include "../../Exceptions/OpenglException.hpp"

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

            OpenglException exception(file, line, (call == nullptr? "" : call), error, (const char*)description);

            Logger::out << exception.what() << std::endl;

            throw exception;

            return true;
        }
    }
}
