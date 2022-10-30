#include "CommandManager.h"

using namespace TMIOSDP;

CommandManager::~CommandManager()
{
    Clear();
}

void CommandManager::Do(Command* command)
{
    command->Execute();
    mHistory.push(command);
}

// To support redo, we can have a cursor concept
void CommandManager::Undo()
{
    Command* command = mHistory.top();
    command->Rollback();
    delete command;
    mHistory.pop();
}

void CommandManager::Clear()
{
    while (!mHistory.empty())
    {
        Command* command = mHistory.top();
        delete command;
        mHistory.pop();
    }
}