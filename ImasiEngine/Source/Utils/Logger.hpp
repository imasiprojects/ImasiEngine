#ifndef IMASIENGINE_LOGGER_HPP
#define IMASIENGINE_LOGGER_HPP

#include <iostream>
#include <fstream>
#include <chrono>

namespace ImasiEngine
{
    class Logger
    {
    private:

        std::string _filename;

    public:

        static Logger out;

        Logger(std::string fileName)
        {
            _filename = fileName;

            #ifdef DEBUG
            {
                std::ofstream outFile(_filename, std::ios::trunc);
                const auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                outFile << ctime(&time);
                outFile << "---------------------------------------------------" << std::endl << std::endl;
                outFile.close();
            }
            #endif
        }

        template <typename T>
        Logger& operator<<(const T& text)
        {
            #ifdef DEBUG
            {
                std::cout << text;
                std::ofstream outFile(_filename, std::ios::app);
                outFile << text;
                outFile.close();
            }
            #endif

            return *this;
        }

        Logger& operator<<(std::ostream&(*function)(std::ostream&))
        {
            #ifdef DEBUG
            {
                std::cout << function;
                std::ofstream outFile;
                outFile.open(_filename, std::ios::app);
                outFile << function;
                outFile.close();
            }
            #endif

            return *this;
        }
    };
}

#endif
