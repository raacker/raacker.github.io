#pragma once 

#include "../Command.h"

namespace TMIOSDP
{
    class Aircraft;
    class ControlTower;
    class CommandSOS : public Command
    {
    public:
        CommandSOS(ControlTower* tower, Aircraft* aircraft);
        Comm::Status Execute() override;
    private:
        ControlTower* mpRefTower;
        Aircraft* mpRefAircraft;
    };
}