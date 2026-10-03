// Game/Unsorted_10B3B2A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Engine/EngineClasses.h"

class AGarrett
{
public:
    char Unknown00[0x4BC];
    AActor* closestAIInRange;
};

// FUNCTION: 0x10B3C050 ?FUN_10b3c050@@YGPAVAPawn@@PAVAGarrett@@@Z
APawn* __stdcall FUN_10b3c050(AGarrett* Garrett)
{
    AActor* Actor = Garrett->closestAIInRange;
    if (Actor)
        return Cast<APawn>(Actor);
    return 0;
}
