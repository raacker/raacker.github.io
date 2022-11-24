#pragma once 

namespace TMIOSDP
{
    class Aircraft;
    class Runaway
    {
    public:
        Runaway(int id) : mRunawayID(id), mpRefOccupant(0) {}
        void SetOccupant(Aircraft* occupant) { mpRefOccupant = occupant; }
        Aircraft* Occupant() { return mpRefOccupant; }
        int ID() { return mRunawayID; }
    private:
        int mRunawayID;
        Aircraft* mpRefOccupant;
    };
}