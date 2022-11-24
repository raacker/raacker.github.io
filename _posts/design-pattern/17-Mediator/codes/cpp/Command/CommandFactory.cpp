#include "CommandFactory.h"

#include "../ControlTower/ControlTower.h"
#include "../Aircrafts/Aircraft.h"

#include "./Commands/CommandLanding.h"
#include "./Commands/CommandDepart.h"
#include "./Commands/CommandGoAround.h"
#include "./Commands/CommandSOS.h"

using namespace TMIOSDP;

Command* CommandFactory::GenerateCommand(CommandType command, ControlTower* tower, Aircraft* aircraft)
{
    switch (command)
    {
    case CommandType::Land:
        return new CommandLanding(tower, aircraft);
    case CommandType::Depart:
        return new CommandDepart(tower, aircraft);
    case CommandType::GoAround:
        return new CommandGoAround(tower, aircraft);
    case CommandType::SOS:
        return new CommandSOS(tower, aircraft);
    }

    return NULL;
}