#include "logger/logger.h"

int main()
{
    Logger logger("demoLog2.log");

    logger.Write("DEBUG", "Application started", "Important");
    logger.Write("DEBUG", "This is the first logger prototype");
    logger.Write("SYSTEM", "Application finished");

    logger.Info("Testing new function");

    logger.Info("Trying to start application");
    logger.Info("Testing category");

    return 0;
}