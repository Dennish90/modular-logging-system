#pragma once

#include <fstream>
#include <string>

class Logger
{
public:
  explicit Logger(const std::string& filePath);

  void Write(const std::string& message);

private:
  std::ofstream _logFile;
};