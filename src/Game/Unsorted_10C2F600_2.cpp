// Game/Unsorted_10C2F600_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10C2F600
{
public:
    void FUN_10c2f600();

    char Unknown00[0x28];
    FVector Unknown28;
    FRotator Unknown34;
    char Unknown40[0x9C];
    int UnknownDC;
};

// FUNCTION: 0x10C2F600 ?FUN_10c2f600@Class_10C2F600@@QAEXXZ
void Class_10C2F600::FUN_10c2f600()
{
    Unknown28 = FVector(0, 0, Unknown28.Z);
    Unknown34 = FRotator(0, 0, 0);
    UnknownDC = 0;
}
