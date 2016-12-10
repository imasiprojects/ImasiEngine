#ifndef IMASIENGINE_INVALIDARGUMENTEXCEPTION_HPP
#define IMASIENGINE_INVALIDARGUMENTEXCEPTION_HPP

#include <exception>
#include <string>

namespace ImasiEngine
{
    class InvalidArgumentException
        : public std::exception
    {
    public:

        const std::string argument;
        const std::string error;

        const std::string message;

        InvalidArgumentException(const std::string& argument, const std::string& error)
            : argument(argument)
            , error(error)
            , message("Invalid argument \"" + this->argument + "\": " + this->error)
        {
        }

        const char* what() const override
        {
            return message.c_str();
        }
    };
}

#endif