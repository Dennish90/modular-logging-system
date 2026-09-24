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
     * @brief Writes a trace-level log entry.
     *
     * Trace entries are intended for very detailed diagnostic information,
     * such as function flow, internal state checks or low-level execution details.
     *
     * If no category is provided, the default category "General" is used.
     *
     * @param message The message to write to the log file.
     * @param category Optional category or module name. Defaults to "General".
     */
    void Trace(const std::string& message, const std::string& category = "General");
    /**
     * @brief Writes a debug-level log entry.
     *
     * Debug entries are intended for information useful during development
     * or troubleshooting, but less detailed than trace entries.
     *
     * If no category is provided, the default category "General" is used.
     *
     * @param message The message to write to the log file.
     * @param category Optional category or module name. Defaults to "General".
     */
    void Debug(const std::string& message, const std::string& category = "General");
    /**
     * @brief Writes an info-level log entry.
     *
     * If no category is provided, the default category "General" is used.
     *
     * @param message The message to write to the log file.
     * @param category Optional category or module name. Defaults to "General".
     */
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
    /**
     * @brief Writes a critical-level log entry.
     *
     * Critical entries are intended for severe errors where the application
     * may not be able to continue safely or correctly.
     *
     * If no category is provided, the default category "General" is used.
     *
     * @param message The message to write to the log file.
     * @param category Optional category or module name. Defaults to "General".
     */
    void Critical(const std::string& message, const std::string& category = "General");
    
    /**
     * @brief Sets the minimum log level that should be written.
     *
     * Log entries below the selected level are ignored by the standard
     * log level helper functions.
     *
     * Level values:
     * 0 = TRACE
     * 1 = DEBUG
     * 2 = INFO
     * 3 = WARNING
     * 4 = ERROR
     * 5 = CRITICAL
     *
     * Values outside this range are clamped to the closest valid level.
     *
     * @param level Minimum log level as an integer from 0 to 5.
     */
    void SetMinimumLogLevel(int level);

    int StringToLogLevel(std::string& strLvl);

private:
    int _minimumLogLevel = 0;
    std::ofstream _logFile;

    // Returns the current local timestamp using the log format:
    // YYYY-MM-DD HH:MM:SS.mmm
    std::string GetCurrentTimestamp() const;
};