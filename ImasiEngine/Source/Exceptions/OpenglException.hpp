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
        const int line;
        const std::string call;

        const int error;
        const std::string description;

        const std::string message;

        OpenglException(const std::string& file, int line, const std::string& call, int error, const std::string& description)
            : file(file)
            , line(line)
            , call(call)
            , error(error)
            , description(description)
            , message("OpenGL error " + std::to_string(error) + " `"
                    + description + "` @ " + file + ":" + std::to_string(line)
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