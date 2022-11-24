#pragma once 

#include "../Command.h"

namespace TMIOSDP
{
    class Aircraft;
    class ControlTower;
    class CommandDepart : public Command
    {
    public:
        CommandDepart(ControlTower* tower, Aircraft* aircraft);
        Comm::Status Execute() override;
    private:
        ControlTower* mpRefTower;
        Aircraft* mpRefAircraft;
    };
}