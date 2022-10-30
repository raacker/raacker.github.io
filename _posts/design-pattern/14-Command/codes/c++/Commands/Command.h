#pragma once

namespace TMIOSDP
{
    class Command
    {
    public:
        virtual ~Command() {};
        virtual void Execute() = 0;

        // Some commands cannot support rollback
        virtual void Rollback() {};
    };
}