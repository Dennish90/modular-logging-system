#include "logger/logger.h"

Logger::Logger(const std::string& filePath)
{
  _logFile.open(filePath, std::ios::app);
}

void Logger::Write(const std::string& message)
{
  if (!_logFile.is_open())
  {
    return;
  }

  _logFile << message << '\n';
}