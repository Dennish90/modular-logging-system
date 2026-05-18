#pragma once

#include <fstream>
#include <string>

#include "logger/logLevel.h"
/**
 * @brief Simple file-based logger for structured log entries.
 *
 * The logger writes entries to a file using the format:
 * timestamp | level | category | message
 *
 * Convenience methods are provided for the default log levels:
 * Info, Warning and Error.
 */
class Logger
{
public:
    /**
     * @brief Creates a logger that writes to the specified log file.
     *
     * If the file already exists, new log entries are appended to it.
     * If the file cannot be opened, the logger prints an error message
     * to the standard error stream and future write operations are ignored.
     *
     * @param filePath Path to the log file.
     */
    explicit Logger(const std::string& filePath);
    /**
     * @brief Writes a log entry with a custom log level.
     *
     * The log entry is written using the format:
     * timestamp | level | category | message
     *
     * If no category is provided, the default category "General" is used.
     *
     * @param level The severity level of the log entry.
     * @param message The message to write to the log file.
     * @param category Optional category or module name. Defaults to "General".
     */
    void Write(std::string level, const std::string& message, const std::string& category = "General");
    /**
     * @brief Writes an info-level log entry.
     *
     * If no category is provided, the default category "General" is used.
     *
     * @param message The message to write to the log file.
     * @param category Optional category or module name. Defaults to "General".
     */
    void Trace(const std::string& message, const std::string& category = "General");
    void Debug(const std::string& message, const std::string& category = "General");
    void Info(const std::string& message, const std::string& category = "General");
    /**
     * @brief Writes a warning-level log entry.
     *
     * If no category is provided, the default category "General" is used.
     *
     * @param message The message to write to the log file.
     * @param category Optional category or module name. Defaults to "General".
     */
    void Warning(const std::string& message, const std::string& category = "General");
    /**
     * @brief Writes an error-level log entry.
     *
     * If no category is provided, the default category "General" is used.
     *
     * @param message The message to write to the log file.
     * @param category Optional category or module name. Defaults to "General".
     */
    void Error(const std::string& message, const std::string& category = "General");
    void Critical(const std::string& message, const std::string& category = "General");
    
    void setMinimumLogLevel(int level);
    int stringToLogLevel(std::string& strLvl);

private:
    // 0 = INFO, 1 = WARNING, 2 = ERROR
    int _minimumLogLevel = 0;
    std::ofstream _logFile;

    std::string GetCurrentTimestamp() const;
};