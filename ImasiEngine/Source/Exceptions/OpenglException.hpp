#ifndef IMASIENGINE_OPENGLEXCEPTION_HPP
#define IMASIENGINE_OPENGLEXCEPTION_HPP

#include <exception>
#include <string>

namespace ImasiEngine
{
    class OpenglException
        : public std::exception
    {
    public:

        const std::string file;
        const unsigned int line;
        const std::string call;

        const int errorCode;
        const std::string errorDescription;

        const std::string message;

        OpenglException(const std::string& file, int line, const std::string& call, int errorCode, const std::string& errorDescription)
            : file(file)
            , line(line)
            , call(call)
            , errorCode(errorCode)
            , errorDescription(errorDescription)
            , message("OpenGL error " + std::to_string(errorCode) + " `"
                    + errorDescription + "` @ " + file + ":" + std::to_string(line)
                    + (call.size() > 0 ? " - `" + call + "`" : ""))
        {
        }

        const char* what() const override
        {
            return message.c_str();
        }
    };
}

#endif