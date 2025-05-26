#pragma once
#include <string>
#include <fstream>

class Logger {
public:
    static Logger& Instance();
    void Log(const std::string& message, const std::string& level = "INFO");

private:
    Logger();
    std::ofstream logFile;
};
