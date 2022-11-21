#include "CommandDepart.h"

#include "../../Aircrafts/Aircraft.h"
#include "../../ControlTower/ControlTower.h"
#include "../../ControlTower/Runaway.h"

using namespace TMIOSDP;

CommandDepart::CommandDepart(ControlTower* tower, Aircraft* aircraft)
    : mpRefTower(tower),
    mpRefAircraft(aircraft)
{
}

Comm::Status CommandDepart::Execute()
{
    Runaway* runaway = mpRefTower->AvailableRunaway();
    if (runaway == NULL)
    {
        return Comm::Status::Deny;
    }

    mpRefAircraft->OccupyRunaway(runaway);
    if (mpRefAircraft->PrepareDeparture() != Comm::Status::Affirmitive)
    {
        return Comm::Status::Deny;
    }

    mpRefAircraft->Depart();
    return Comm::Status::Affirmitive;
}