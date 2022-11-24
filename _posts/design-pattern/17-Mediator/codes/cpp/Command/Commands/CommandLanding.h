#pragma once 

#include "../Command.h"

namespace TMIOSDP
{
    class Aircraft;
    class ControlTower;
    class CommandLanding : public Command
    {
    public:
        CommandLanding(ControlTower* tower, Aircraft* aircraft);
        Comm::Status Execute() override;
    private:
        ControlTower* mpRefTower;
        Aircraft* mpRefAircraft;
    };
}