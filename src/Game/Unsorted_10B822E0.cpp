// Game/Unsorted_10B822E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

extern float DAT_11006e34;

class Class_10AA9DA0
{
public:
    void* FUN_10aa9da0();
};

class Class_10B822E0
{
public:
    FVector FUN_10b822e0();

    char Unknown00[0x7C];
    Class_10AA9DA0* Unknown7C;
};

// FUNCTION: 0x10B822E0 ?FUN_10b822e0@Class_10B822E0@@QAE?AVFVector@@XZ
FVector Class_10B822E0::FUN_10b822e0()
{
    const FVector* V = (const FVector*)Unknown7C->FUN_10aa9da0();
    return FVector(V->X, V->Y, V->Z) * DAT_11006e34;
}
