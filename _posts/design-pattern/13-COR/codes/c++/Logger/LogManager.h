#pragma once
#include "Logger.h"
#include <list>

namespace TMIOSDP
{
    class LogManager
    {
    public:
        ~LogManager();
        void AssignLogger(Logger* logger);
        void RemoveLogger(Logger* logger);
        void Log(const std::string& message, Logger::Severity severity);
    private:
        std::list<Logger*> mLoggers;
    };
}