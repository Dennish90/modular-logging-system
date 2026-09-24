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
        Logger::Write("INFO", "---- [LOGGER SESSION STARTED] ----", "LOGGER");
    }
}

void Logger::Write(std::string level, const std::string& message, const std::string& category)
{
    if (!_logFile.is_open())
    {
        return;
    }

    _logFile << GetCurrentTimestamp()
             << " | "
             << level 
             << " | " 
             << category 
             << " | "
             << message
             << '\n';
}

void Logger::Trace(const std::string& message, const std::string& category)
{
    if(_minimumLogLevel > 0) return;
    Write("TRACE", message, category);
}
void Logger::Debug(const std::string& message, const std::string& category)
{
    if(_minimumLogLevel > 1) return;
    Write("DEBUG", message, category);
}

void Logger::Info(const std::string& message, const std::string& category)
{
    if(_minimumLogLevel > 2) return;
    Write("INFO", message, category);
}

void Logger::Warning(const std::string& message, const std::string& category)
{
    if(_minimumLogLevel > 3) return;
    Write("WARNING", message, category);
}

void Logger::Error(const std::string& message, const std::string& category)
{
    if(_minimumLogLevel > 4) return;
    Write("ERROR", message, category);
}

void Logger::Critical(const std::string& message, const std::string& category)
{
    Write("CRITICAL", message, category);
}

void Logger::setMinimumLogLevel(int level)
{
    if(level > 5) _minimumLogLevel = 5;
    else if(level < 0) _minimumLogLevel = 0;
    else _minimumLogLevel = level;
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