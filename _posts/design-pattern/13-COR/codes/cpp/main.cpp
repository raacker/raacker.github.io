#include "./Logger/LogManager.h"

using namespace TMIOSDP;

int main()
{
    LogManager manager;
    
    manager.AssignLogger(EmailLogger::createEmailLogger("haven.cpp@gmail.com"));
    manager.AssignLogger(SlackLogger::createSlackLogger("itshaven"));
    manager.AssignLogger(FileLogger::createFileLogger("Log.log"));

    manager.Log("Exception occured!!", Logger::Severity::ERROR);
}