#include <iostream>

#include "logger/logger.h"

Logger::Logger(const std::string& filePath)
{
    _logFile.open(filePath, std::ios::app);

    if(!_logFile.is_open())
    {
        std::cerr << "Could not initialize logger module. Log file could not be opened: "
                  << filePath << '\n';
    }

    else
    {
        Logger::Write(LogLevel::Info, "---- [LOGGER SESSION STARTED] ----");
    }
}

void Logger::Write(LogLevel level, const std::string& message)
{
    if (!_logFile.is_open())
    {
        return;
    }

    _logFile << logLevelToString(level) << " | " << message << '\n';
}

void Logger::Info(const std::string& message)
{
    Write(LogLevel::Info, message);
}

void Logger::Warning(const std::string& message)
{
    Write(LogLevel::Warning, message);
}

void Logger::Error(const std::string& message)
{
    Write(LogLevel::Error, message);
}

std::string Logger::logLevelToString(LogLevel level) const
{
    switch (level)
    {
        case LogLevel::Info:
            return "INFO";
            break;
        case LogLevel::Warning:
            return "WARNING";
            break;
        case LogLevel::Error:
            return "ERROR";
            break;
        default:
            return "UNKNOWN";
            break;
    }
}