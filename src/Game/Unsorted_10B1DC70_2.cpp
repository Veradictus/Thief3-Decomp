// Game/Unsorted_10B1DC70_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

struct Struct_10B1DCA0_Param
{
    char Unknown00[0x400];
    FRotator Unknown400;
};

struct Struct_10B1DCA0
{
    Struct_10B1DCA0() {}
    Struct_10B1DCA0(const FVector& InOrigin)
        : Unknown00(InOrigin),
          Unknown0C(1.0f, 0.0f, 0.0f),
          Unknown18(0.0f, 1.0f, 0.0f),
          Unknown24(0.0f, 0.0f, 1.0f)
    {
    }

    void FUN_109620b0(const FRotator& R);

    FVector Unknown00;
    FVector Unknown0C;
    FVector Unknown18;
    FVector Unknown24;
};

class Class_10A37860
{
public:
    bool FUN_10a37860();

    char Unknown00[0xC];
    FRotator Unknown0C;
};

class Class_10F3A3D8
{
public:
    char Unknown00[0x10];
    Class_10A37860* Unknown10;
};

extern Class_10F3A3D8* DAT_10f3a3d8;

// FUNCTION: 0x10B1DCA0 ?FUN_10b1dca0@@YA?AUStruct_10B1DCA0@@PAUStruct_10B1DCA0_Param@@@Z
Struct_10B1DCA0 FUN_10b1dca0(Struct_10B1DCA0_Param* p1)
{
    Struct_10B1DCA0 Coords(FVector(0.0f, 0.0f, 0.0f));
    if (DAT_10f3a3d8->Unknown10->FUN_10a37860())
        Coords.FUN_109620b0(p1->Unknown400);
    else
        Coords.FUN_109620b0(DAT_10f3a3d8->Unknown10->Unknown0C);
    return Coords;
}
