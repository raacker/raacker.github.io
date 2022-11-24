#include "CommandLanding.h"

#include "../../Aircrafts/Aircraft.h"
#include "../../ControlTower/ControlTower.h"

using namespace TMIOSDP;

CommandLanding::CommandLanding(ControlTower* tower, Aircraft* aircraft)
    : mpRefTower(tower),
    mpRefAircraft(aircraft)
{
}

Comm::Status CommandLanding::Execute()
{
    Runaway* runaway = mpRefTower->AvailableRunaway();
    if (runaway == NULL)
    {
        return mpRefAircraft->GoAround();
    }

    mpRefAircraft->OccupyRunaway(runaway);

    Gate* gate = mpRefTower->AvailableGate();
    if (gate == NULL)
    {
        return Comm::Status::Onhold;
    }

    mpRefAircraft->OccupyGate(gate);

    if (mpRefAircraft->PrepareLanding() != Comm::Status::Affirmitive)
    {
        return Comm::Status::Deny;
    }

    mpRefAircraft->Land();
    return Comm::Status::Affirmitive;
}