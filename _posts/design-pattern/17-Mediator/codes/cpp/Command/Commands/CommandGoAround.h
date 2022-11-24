#pragma once 

#include "../Command.h"

namespace TMIOSDP
{
    class Aircraft;
    class ControlTower;
    class CommandGoAround : public Command
    {
    public:
        CommandGoAround(ControlTower* tower, Aircraft* aircraft);
        Comm::Status Execute() override;
    private:
        ControlTower* mpRefTower;
        Aircraft* mpRefAircraft;
    };
}