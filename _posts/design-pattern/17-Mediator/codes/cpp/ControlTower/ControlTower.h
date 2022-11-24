#pragma once 

#include <list>
#include <queue>
#include "../CommProtocol/CommProtocol.h"
#include "../Command/CommandFactory.h"

namespace TMIOSDP
{
    class Aircraft;
    class Runaway;
    class Gate;
    class Command;
    class ControlTower
    {
    public:
        ControlTower(const std::list<Runaway*>& runaways,
            const std::list<Gate*>& gates);
        ~ControlTower();
        void Request(CommandType type, Aircraft* aircraft);
        void ResolveCommand();
        void Register(Aircraft* aircraft);
        void Unregister(Aircraft* aircraft);

        Runaway* AvailableRunaway();
        Gate* AvailableGate();
    private:
        std::list<Aircraft*> mAircrafts;
        std::list<Runaway*> mRunaways;
        std::list<Gate*> mGates;
        std::queue<Command*> mCommandQueue;
    };
}