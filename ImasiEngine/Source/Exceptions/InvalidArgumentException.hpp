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

        InvalidArgumentException(const std::string& argument, const std::string& error)
            : argument(argument)
            , error(error)
        {
        }

        const char* what() const override
        {
            return ("Invalid argument \"" + this->argument + "\": " + this->error).c_str();
        }
    };
}

#endif