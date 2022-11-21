#pragma once 

namespace TMIOSDP
{
    class Aircraft;
    class Gate
    {
    public:
        Gate(int id) : mGateID(id), mpRefOccupant(0) {}
        void SetOccupant(Aircraft* occupant) { mpRefOccupant = occupant; }
        Aircraft* Occupant() { return mpRefOccupant; }
        int ID() { return mGateID; }
    private:
        int mGateID;
        Aircraft* mpRefOccupant;
    };
}