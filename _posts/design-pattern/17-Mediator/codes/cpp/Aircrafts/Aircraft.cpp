#include "Aircraft.h"

#include "../ControlTower/ControlTower.h"
#include "../ControlTower/Runaway.h"
#include "../ControlTower/Gate.h"
#include "../Command/CommandFactory.h"

#include <iostream>

using namespace TMIOSDP;

Aircraft::Aircraft(ControlTower* controlTower,
    const AircraftInfo& info,
    const FlightSchedule& schedule)
        : mInfo(info),
          mCurrSchedule(schedule),
          mpRefAssignedRunaway(NULL)
{
    SetControlTower(controlTower);
}

void Aircraft::SetControlTower(ControlTower* controlTower)
{
    if (mpRefControlTower != NULL)
        mpRefControlTower->Unregister(this);

    mpRefControlTower = controlTower;
    mpRefControlTower->Register(this);
}

void Aircraft::OccupyRunaway(Runaway* runaway)
{
    runaway->SetOccupant(this);
    mpRefAssignedRunaway = runaway;
}
void Aircraft::OccupyGate(Gate* gate)
{
    gate->SetOccupant(this);
    mpRefAssignedGate = gate;
}

void Aircraft::RequestLanding()
{
    mpRefControlTower->Request(CommandType::Land, this);
}

Comm::Status Aircraft::PrepareLanding()
{
    LandingGear(true);
    SetSpeed(200);
    return Comm::Status::Affirmitive;
}

Comm::Status Aircraft::Land()
{
    MoveToGate();
    Engine(false);

    PrintAircraftInfo();
    std::cout << "Landed" << std::endl;

    mpRefAssignedRunaway = NULL;
    return Comm::Status::Affirmitive;
}

void Aircraft::RequestDeparture()
{
    mpRefControlTower->Request(CommandType::Depart, this);
}
Comm::Status Aircraft::PrepareDeparture()
{
    Engine(true);
    MoveToRunaway();
    return Comm::Status::Affirmitive;
}

Comm::Status Aircraft::Depart()
{
    SetSpeed(1000);
    LandingGear(false);

    PrintAircraftInfo();
    std::cout << "Departed" << std::endl;
    
    mpRefAssignedGate = NULL;
    return Comm::Status::Affirmitive;
}

Comm::Status Aircraft::GoAround()
{
    SetSpeed(500);
    PrintAircraftInfo();
    std::cout << "Landing Failed, Go Around" << std::endl;
    return Comm::Status::Affirmitive;
}

void Aircraft::RequestSOS()
{
    mpRefControlTower->Request(CommandType::SOS, this);
}

void Aircraft::PrintAircraftInfo()
{
    std::cout << "[Comm] " << mInfo.companyName << "-" << mInfo.modelName << " ";
}

bool Aircraft::Engine(bool on)
{
    PrintAircraftInfo();
    std::cout << "Engine" << (on ? "On" : "Off") << std::endl;
    return true;
}
bool Aircraft::LandingGear(bool open)
{
    PrintAircraftInfo();
    std::cout << "Landing Gear " << (open ? "Down" : "Up") << std::endl;
    return true;
}

bool Aircraft::SetSpeed(double speed)
{
    PrintAircraftInfo();
    mFlightStatus.speed = speed;
    std::cout << "Set Speed to " << speed << std::endl;
    return true;
}

bool Aircraft::SetAltitude(double alt)
{
    PrintAircraftInfo();
    mFlightStatus.altitude = alt;
    std::cout << "Set Altitude to " << alt << std::endl;
    return true;
}

double Aircraft::GetSpeed()
{
    PrintAircraftInfo();
    return mFlightStatus.speed;
}

double Aircraft::GetTravelDist()
{
    PrintAircraftInfo();
    return mFlightStatus.travelDistance;
}

bool Aircraft::MoveToRunaway()
{
    PrintAircraftInfo();

    if (mpRefAssignedRunaway == NULL)
    {
        std::cout << "There is no assigned runaway. Cannot prepare" << std::endl;
        return false;
    }

    std::cout << "Move to Runaway " << mpRefAssignedRunaway->ID() << std::endl;
    return true;
}

bool Aircraft::MoveToGate()
{
    PrintAircraftInfo();

    if (mpRefAssignedGate == NULL)
    {
        std::cout << "There is no assigned gate. Cannot prepare" << std::endl;
        return false;
    }

    std::cout << "Move to Gate " << mpRefAssignedGate->ID() << std::endl;
    return true;
}