#include <logger/logger.h>

int main()
{
  Logger logger("demoLog.txt");

  logger.Write("Application started");
  logger.Write("This is the first logger prototype");
  logger.Write("Application finished");

  return 0;
}