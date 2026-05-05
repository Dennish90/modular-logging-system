#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

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

void Logger::Write(LogLevel level, const std::string& message, const std::string& category)
{
    if (!_logFile.is_open())
    {
        return;
    }

    _logFile << GetCurrentTimestamp()
             << " | "
             << logLevelToString(level) 
             << " | " 
             << category 
             << " | "
             << message
             << '\n';
}

void Logger::Info(const std::string& message, const std::string& category)
{
    Write(LogLevel::Info, message, category);
}

void Logger::Warning(const std::string& message, const std::string& category)
{
    Write(LogLevel::Warning, message, category);
}

void Logger::Error(const std::string& message, const std::string& category)
{
    Write(LogLevel::Error, message, category);
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

std::string Logger::GetCurrentTimestamp() const
{
    const auto now = std::chrono::system_clock::now();
    const std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    std::tm localTime{};

#if defined(_WIN32)
    localtime_s(&localTime, &currentTime);
#else
    localtime_r(&currentTime, &localTime);
#endif

    const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()
    ) % 1000;

    std::ostringstream timestampStream;

    timestampStream << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S")
                    << '.'
                    << std::setfill('0')
                    << std::setw(3)
                    << milliseconds.count();

    return timestampStream.str();
}