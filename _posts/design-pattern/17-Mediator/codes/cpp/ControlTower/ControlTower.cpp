#include "ControlTower.h"

#include "../Aircrafts/Aircraft.h"
#include "Runaway.h"
#include "Gate.h"
#include "../Command/Command.h"
#include "../Command/CommandFactory.h"

using namespace TMIOSDP;

ControlTower::ControlTower(const std::list<Runaway*>& runaways,
        const std::list<Gate*>& gates)
    : mRunaways(runaways), mGates(gates)
{

}

ControlTower::~ControlTower()
{
    for (Runaway* runaway : mRunaways)
    {
        delete runaway;
    }
    mRunaways.clear();

    for (Gate* gate : mGates)
    {
        delete gate;
    }
    mGates.clear();
}

void ControlTower::Request(CommandType type, Aircraft* aircraft)
{
    Command* newCommand = CommandFactory::GenerateCommand(type, this, aircraft);
    mCommandQueue.push(newCommand);
}

void ControlTower::ResolveCommand()
{
    if (mCommandQueue.empty())
        return;

    Command* command = mCommandQueue.front();
    mCommandQueue.pop();

    command->Execute();
    delete command;
}

void ControlTower::Register(Aircraft* aircraft)
{
    auto searchResult = std::find(mAircrafts.begin(), mAircrafts.end(), aircraft);
    if (searchResult != mAircrafts.end())
        return;

    mAircrafts.push_back(aircraft);
}

void ControlTower::Unregister(Aircraft* aircraft)
{
    auto searchResult = std::find(mAircrafts.begin(), mAircrafts.end(), aircraft);
    if (searchResult == mAircrafts.end())
        return;

    mAircrafts.erase(searchResult);
}

Runaway* ControlTower::AvailableRunaway()
{
    auto searchResult = std::find_if(mRunaways.begin(), mRunaways.end(),
        [](Runaway* runaway) { return runaway->Occupant() == NULL; });

    if (searchResult == mRunaways.end())
        return NULL;

    return *searchResult;
}

Gate* ControlTower::AvailableGate()
{
    auto searchResult = std::find_if(mGates.begin(), mGates.end(),
        [](Gate* gate) { return gate->Occupant() == NULL; });

    if (searchResult == mGates.end())
        return NULL;

    return *searchResult;
}