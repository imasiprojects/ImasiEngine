#pragma once

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

        explicit Logger(std::string fileName)
        {
            _filename = fileName;

            std::ofstream outFile(_filename, std::ios::trunc);
            const auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            outFile << ctime(&time);
            outFile << "---------------------------------------------------" << std::endl;
            outFile.close();
        }

        template <typename T> Logger& operator<<(const T& text)
        {
            std::cout << text;
            std::ofstream outFile(_filename, std::ios::app);
            outFile << text;
            outFile.close();

            return *this;
        }

        Logger& operator<<(std::ostream&(*function)(std::ostream&))
        {
            std::cout << function;
            std::ofstream outFile;
            outFile.open(_filename, std::ios::app);
            outFile << function;
            outFile.close();

            return *this;
        }
    };
}
