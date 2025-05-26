#include "pch.h"
#include "Logger.h"
#include <ctime>

Logger::Logger() {
    logFile.open("log.txt", std::ios::app);
}

Logger& Logger::Instance() {
    static Logger instance;
    return instance;
}

void Logger::Log(const std::string& message, const std::string& level) {
    std::time_t now = std::time(nullptr);
    char timeStr[26];
    ctime_s(timeStr, sizeof(timeStr), &now);
    timeStr[24] = '\0'; // удаление '\n'
    logFile << "[" << timeStr << "] [" << level << "] " << message << std::endl;
}

