#pragma once

#include <fstream>
#include <string>

#include "logger/logLevel.h"

class Logger
{
public:
    explicit Logger(const std::string& filePath);

    void Write(LogLevel level, const std::string& message);
    void Info(const std::string& message);
    void Warning(const std::string& message);
    void Error(const std::string& message);

private:
    std::ofstream _logFile;

    std::string logLevelToString(LogLevel level) const;
};