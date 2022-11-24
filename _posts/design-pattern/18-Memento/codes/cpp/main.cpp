#include "Originator.h"

using namespace TMIOSDP;

int main()
{
    Originator originator;
    originator.SetInfo({ "Haven", "Vancouver", "236-567-1234" });
    
    originator.PrintCurrentInfo();
    originator.SaveState();

    originator.SetInfo({ "Ken", "Burnaby", "236-765-4321" });
    originator.PrintCurrentInfo();

    originator.RestoreState();
    originator.PrintCurrentInfo();
}