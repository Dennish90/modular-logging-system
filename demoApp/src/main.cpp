#include <logger/logger.h>

#include <chrono>
#include <random>
#include <string>
#include <thread>
#include <vector>

int main()
{
    Logger logger("demoLog.log");

    const std::vector<std::string> categories =
    {
        "System",
        "Config",
        "Network",
        "Database",
        "FileSystem",
        "UserInterface",
        "Security",
        "Performance"
    };

    const std::vector<std::string> traceMessages =
    {
        "Entering update loop",
        "Checking internal state",
        "Reading cached value",
        "Validating temporary data",
        "Leaving function scope"
    };

    const std::vector<std::string> debugMessages =
    {
        "Loaded runtime setting",
        "Generated request payload",
        "Database query prepared",
        "Cache lookup completed",
        "UI state updated"
    };

    const std::vector<std::string> infoMessages =
    {
        "Application started",
        "Configuration loaded successfully",
        "User opened main window",
        "Database query completed",
        "Network request completed",
        "Background task finished"
    };

    const std::vector<std::string> warningMessages =
    {
        "Configuration value missing, using default",
        "Network response took longer than expected",
        "Low disk space warning",
        "Retrying failed operation",
        "Deprecated setting detected"
    };

    const std::vector<std::string> errorMessages =
    {
        "Failed to open requested file",
        "Database connection failed",
        "Network request failed",
        "Could not parse configuration file",
        "Permission denied while accessing resource"
    };

    const std::vector<std::string> criticalMessages =
    {
        "Critical system dependency unavailable",
        "Application entered unrecoverable state",
        "Security validation failed critically",
        "Fatal error during startup",
        "Data integrity check failed"
    };

    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());

    std::uniform_int_distribution<int> categoryDistribution(0, static_cast<int>(categories.size()) - 1);
    std::uniform_int_distribution<int> levelDistribution(0, 99);

    logger.Info("Demo application started", "System");

    for (int i = 0; i < 1000; i++)
    {
        const std::string& category = categories[categoryDistribution(generator)];
        const int levelRoll = levelDistribution(generator);

        if (levelRoll < 20)
        {
            std::uniform_int_distribution<int> messageDistribution(0, static_cast<int>(traceMessages.size()) - 1);
            logger.Trace(traceMessages[messageDistribution(generator)], category);
        }
        else if (levelRoll < 45)
        {
            std::uniform_int_distribution<int> messageDistribution(0, static_cast<int>(debugMessages.size()) - 1);
            logger.Debug(debugMessages[messageDistribution(generator)], category);
        }
        else if (levelRoll < 80)
        {
            std::uniform_int_distribution<int> messageDistribution(0, static_cast<int>(infoMessages.size()) - 1);
            logger.Info(infoMessages[messageDistribution(generator)], category);
        }
        else if (levelRoll < 92)
        {
            std::uniform_int_distribution<int> messageDistribution(0, static_cast<int>(warningMessages.size()) - 1);
            logger.Warning(warningMessages[messageDistribution(generator)], category);
        }
        else if (levelRoll < 98)
        {
            std::uniform_int_distribution<int> messageDistribution(0, static_cast<int>(errorMessages.size()) - 1);
            logger.Error(errorMessages[messageDistribution(generator)], category);
        }
        else
        {
            std::uniform_int_distribution<int> messageDistribution(0, static_cast<int>(criticalMessages.size()) - 1);
            logger.Critical(criticalMessages[messageDistribution(generator)], category);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    logger.Info("Demo application finished", "System");

    return 0;
}