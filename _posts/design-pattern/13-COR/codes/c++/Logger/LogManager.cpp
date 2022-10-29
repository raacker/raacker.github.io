#include "LogManager.h"

using namespace TMIOSDP;

LogManager::~LogManager()
{
    for (Logger* logger : mLoggers)
    {
        delete logger;
    }
    mLoggers.clear();
}

void LogManager::AssignLogger(Logger* logger)
{
    mLoggers.push_back(logger);
}

void LogManager::RemoveLogger(Logger* logger)
{
    mLoggers.remove(logger);
    delete logger;
}

// This part can be a flag-based check with pre-allocated loggers
void LogManager::Log(const std::string& message, Logger::Severity severity)
{
    for (Logger* logger : mLoggers)
    {
        logger->log(message, severity);
    }
}