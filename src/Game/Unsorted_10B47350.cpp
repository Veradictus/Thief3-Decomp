// Game/Unsorted_10B47350.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10993E20
{
public:
    void FUN_10993e20(int A);
};

class Class_10B7AC30
{
public:
    float FUN_10b7ac30();
};

class Class_10B473D0_Unknown10
{
public:
    char Unknown00[0x4A1];
    bool Unknown4A1;
};

class Class_10B473D0
{
public:
    void FUN_10b473d0();
    FVector FUN_10b47220();

    char Unknown00[4];
    Class_10993E20* Unknown04;
    Class_10B7AC30* Unknown08;
    char Unknown0C[4];
    Class_10B473D0_Unknown10* Unknown10;
    char Unknown14[8];
    bool Unknown1C;
    bool Unknown1D;
    char Unknown1E[2];
    FVector Unknown20;
    float Unknown2C;
};

// FUNCTION: 0x10B473D0 ?FUN_10b473d0@Class_10B473D0@@QAEXXZ
void Class_10B473D0::FUN_10b473d0()
{
    if (Unknown1C)
    {
        Unknown1D = true;
        Unknown10->Unknown4A1 = false;
        Unknown04->FUN_10993e20(0);
        Unknown20 = FUN_10b47220();
        Unknown2C = Unknown08->FUN_10b7ac30();
    }
}
