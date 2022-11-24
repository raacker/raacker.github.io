#pragma once 

#include "../Command.h"

namespace TMIOSDP
{
    class Aircraft;
    class ControlTower;
    class CommandChangeAltitude : public Command
    {
    public:
        CommandChangeAltitude(ControlTower* tower, Aircraft* aircraft);
        Comm::Status Execute() override;
    private:
        ControlTower* mpRefTower;
        Aircraft* mpRefAircraft;
    };
}