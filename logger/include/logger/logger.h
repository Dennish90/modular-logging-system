#pragma once

#include <fstream>
#include <string>

#include "logger/logLevel.h"

class Logger
{
public:
    explicit Logger(const std::string& filePath);

    void Write(LogLevel level, const std::string& message, const std::string& category = "General");
    void Info(const std::string& message, const std::string& category = "General");
    void Warning(const std::string& message, const std::string& category = "General");
    void Error(const std::string& message, const std::string& category = "General");

private:
    std::ofstream _logFile;

    std::string logLevelToString(LogLevel level) const;
    std::string GetCurrentTimestamp() const;
};