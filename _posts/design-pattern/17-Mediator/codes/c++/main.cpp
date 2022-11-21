#include "./ControlTower/ControlTower.h"
#include "./ControlTower/Runaway.h"
#include "./ControlTower/Gate.h"
#include "./Aircrafts/Aircraft.h"
#include "./date/date.h"

using namespace TMIOSDP;

int main()
{
    ControlTower* yvrControlTower = new ControlTower(
        { new Runaway(0), new Runaway(1), new Runaway(2) },
        { new Gate(0), new Gate(1), new Gate(2) });

    Aircraft* airCanada = new Aircraft(yvrControlTower,
        { Aircraft::Type::AIRPLANE, "Boing 737", "AirCanada" },
        { "YVR", "ICN", date::format("%Y%m%d %H:%M:%S", std::chrono::system_clock::now()) });
    Aircraft* koreanAir = new Aircraft(yvrControlTower,
        { Aircraft::Type::AIRPLANE, "Boing 737", "KoreanAir" },
        { "YVR", "YYC", date::format("%Y%m%d %H:%M:%S", std::chrono::system_clock::now()) });

    airCanada->RequestDeparture();
    koreanAir->RequestDeparture();

    yvrControlTower->ResolveCommand();
    yvrControlTower->ResolveCommand();

    delete yvrControlTower;
    delete airCanada;
    delete koreanAir;
}