// Game/Unsorted_10C51600.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

extern void* DAT_10e9bea0;

class Class_10c531f0
{
public:
    void* Unknown00;
    void FUN_10c531f0();
};

struct Struct_10C516B0
{
};

class Class_10C516B0
{
public:
    void FUN_10c516b0();
    void FUN_10c50d40();

    char Unknown00[4];
    Struct_10C516B0* Unknown04;
};

class Class_10C4E880
{
public:
    int FUN_10c4eb60(const FVector* Point);
};

Class_10C4E880* FUN_10c51550();

// FUNCTION: 0x10C51670 ?FUN_10c51670@@YG_NPBVFVector@@0@Z
bool __stdcall FUN_10c51670(const FVector* A, const FVector* B)
{
    return FUN_10c51550()->FUN_10c4eb60(A) != FUN_10c51550()->FUN_10c4eb60(B);
}

// FUNCTION: 0x10C531F0 ?FUN_10c531f0@Class_10c531f0@@QAEXXZ
void Class_10c531f0::FUN_10c531f0()
{
    Unknown00 = &DAT_10e9bea0;
}
