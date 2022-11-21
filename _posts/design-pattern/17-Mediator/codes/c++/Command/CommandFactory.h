#pragma once

namespace TMIOSDP
{
    // Limit Executable Commands by defining enums
    enum class CommandType : int
    {
        Land,
        Depart,
        GoAround,
        SOS,
    };

    class Command;
    class ControlTower;
    class Aircraft;
    class CommandFactory
    {
    public:
        static Command* GenerateCommand(CommandType command, ControlTower* tower, Aircraft* aircraft);
    };
}