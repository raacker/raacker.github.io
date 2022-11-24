#include "CommandGoAround.h"

#include "../../Aircrafts/Aircraft.h"
#include "../../ControlTower/ControlTower.h"

using namespace TMIOSDP;

CommandGoAround::CommandGoAround(ControlTower* tower, Aircraft* aircraft)
    : mpRefTower(tower),
    mpRefAircraft(aircraft)
{
}

Comm::Status CommandGoAround::Execute()
{
    std::cout << "Go Around" << std::endl;
    return Comm::Status::Affirmitive;
}