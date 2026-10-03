// Game/Unsorted_10C16300_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class AActor
{
    DECLARE_CLASS(AActor, UObject, 0x800, Engine)
};

class Class_10C16300
{
public:
    AActor* FUN_10c16300();

    char Unknown00[4];
    UObject* Unknown04;
};

// FUNCTION: 0x10C16300 ?FUN_10c16300@Class_10C16300@@QAEPAVAActor@@XZ
AActor* Class_10C16300::FUN_10c16300()
{
    if (Unknown04 && Unknown04->IsA(AActor::StaticClass()))
        return (AActor*)Unknown04;
    return 0;
}
