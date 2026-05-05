#include <logger/logger.h>

int main()
{
    Logger logger("demoLog.txt");

    logger.Write(LogLevel::Info, "Application started");
    logger.Write(LogLevel::Info, "This is the first logger prototype");
    logger.Write(LogLevel::Info, "Application finished");

    logger.Info("Testing new function");
    logger.Error("Could not open file");

    logger.Info("Testing category");
    logger.Warning("Too cool for shool", "Coolness");
    return 0;
}