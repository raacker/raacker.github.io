#include "CommandSOS.h"

#include "../../Aircrafts/Aircraft.h"
#include "../../ControlTower/ControlTower.h"

using namespace TMIOSDP;

CommandSOS::CommandSOS(ControlTower* tower, Aircraft* aircraft)
    : mpRefTower(tower),
    mpRefAircraft(aircraft)
{
}

Comm::Status CommandSOS::Execute()
{
    std::cout << "SOS!!" << std::endl;
    return Comm::Status::Affirmitive;
}