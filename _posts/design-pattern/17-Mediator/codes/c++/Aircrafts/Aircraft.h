#pragma once 

#include <string>
#include "../date/date.h"
#include "../CommProtocol/CommProtocol.h"

namespace TMIOSDP
{
    class ControlTower;
    class Runaway;
    class Gate;
    class Aircraft
    {
    public:
        enum class Type : int 
        {
            AIRPLANE,
            HELICOPTER,
            AIRSHIP,
            HOT_AIR_BALLOON
        };

        struct FlightSchedule
        {
            std::string from = "";
            std::string to = "";
            std::string scheduledDepartureTime;
        };

        struct AircraftInfo
        {
            Type type;
            std::string modelName = "";
            std::string companyName = "";
        };

        struct FlightStatus
        {
            double speed = 0;
            double altitude = 0;
            double travelDistance = 0;
        };

        Aircraft(ControlTower* controlTower,
            const AircraftInfo& info,
            const FlightSchedule& schedule);

        void SetControlTower(ControlTower* controlTower);
        void OccupyRunaway(Runaway* runaway);
        void OccupyGate(Gate* gate);

        void RequestLanding();
        Comm::Status PrepareLanding();
        Comm::Status Land();

        void RequestDeparture();
        Comm::Status PrepareDeparture();
        Comm::Status Depart();

        Comm::Status GoAround();

        void RequestSOS();

        bool SetSpeed(double speed);
        bool SetAltitude(double alt);

    protected:
        void PrintAircraftInfo();
        bool Engine(bool on);
        bool LandingGear(bool open);
        double GetSpeed();
        double GetTravelDist();
        bool MoveToRunaway();
        bool MoveToGate();

    private:
        ControlTower* mpRefControlTower;
        Runaway* mpRefAssignedRunaway;
        Gate* mpRefAssignedGate;
        AircraftInfo mInfo;
        FlightSchedule mCurrSchedule;
        FlightStatus mFlightStatus;
    };
}