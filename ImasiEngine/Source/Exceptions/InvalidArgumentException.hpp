#ifndef IMASIENGINE_INVALIDARGUMENTEXCEPTION_HPP
#define IMASIENGINE_INVALIDARGUMENTEXCEPTION_HPP

#include <string>

namespace ImasiEngine
{
    class InvalidArgumentException : public std::exception
    {
    private:

        std::string _argumentName;
        std::string _errorDescription;

    public:

        InvalidArgumentException(const std::string& argumentName, const std::string& errorDescription)
        {
            _argumentName = argumentName;
            _errorDescription = errorDescription;
        }
    };
}

#endif