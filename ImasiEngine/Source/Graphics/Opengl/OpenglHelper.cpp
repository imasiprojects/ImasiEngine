#include "OpenglHelper.hpp"

#include <GL/glew.h>

#include "../../Utils/Logger.hpp"
#include "../../Exceptions/OpenglException.hpp"

namespace ImasiEngine
{
    namespace OpenglHelper
    {
        void beginSfml(sf::RenderTarget& renderTarget)
        {
            renderTarget.pushGLStates();
        }

        void endSfml(sf::RenderTarget& renderTarget)
        {
            renderTarget.popGLStates();
        }

        bool checkError(const char* file, const int line, const char* call)
        {
            const GLenum error = glGetError();

            if (error == GL_NO_ERROR)
            {
                return false;
            }

            const char* description;

            switch (error)
            {
                case GL_INVALID_ENUM:                   description = "Invalid enum"; break;
                case GL_INVALID_VALUE:                  description = "Invalid value"; break;
                case GL_INVALID_OPERATION:              description = "Invalid operation"; break;
                case GL_STACK_OVERFLOW:                 description = "Stack overflow"; break;
                case GL_STACK_UNDERFLOW:                description = "Stack underflow"; break;
                case GL_OUT_OF_MEMORY:                  description = "Out of memory"; break;
                case GL_INVALID_FRAMEBUFFER_OPERATION:  description = "Invalid framebuffer operation"; break;
                default:                                description = "Unknown error"; break;
            }

            OpenglException exception(file, line, (call == nullptr ? "" : call), error, description);

            Logger::out << exception.what() << std::endl;

            throw exception;

            return true;
        }
    }
}
