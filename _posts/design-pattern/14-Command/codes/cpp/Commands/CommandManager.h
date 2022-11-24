#pragma once
#include "Command.h"
#include <stack>

namespace TMIOSDP
{
    class CommandManager
    {
    public:
        ~CommandManager();
        void Do(Command* command);
        void Undo();
        void Clear();
    private:
        std::stack<Command*> mHistory;
    };
}