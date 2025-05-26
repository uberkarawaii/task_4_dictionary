#pragma once
#include <string>
#include <fstream>

class Logger {
public:
    static Logger& Instance();
    void Log(const std::string& message, const std::string& level = "INFO");
    void LogWarning(const std::string& message);
private:
    Logger();
    std::ofstream logFile;
};
