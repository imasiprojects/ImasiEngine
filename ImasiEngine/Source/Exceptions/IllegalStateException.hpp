#ifndef IMASIENGINE_ILLEGALSTATEEXCEPTION_HPP
#define IMASIENGINE_ILLEGALSTATEEXCEPTION_HPP

#include <exception>
#include <string>

namespace ImasiEngine
{
    class IllegalStateException
        : public std::exception
    {
    public:

        const std::string message;

        IllegalStateException(const std::string& reason)
            : message("Illegal state: " + reason)
        {
        }

        const char* what() const override
        {
            return message.c_str();
        }
    };
}

#endif