// Game/Unsorted_10B1DC70_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

struct Struct_10B1DD70_Param
{
    char Unknown00[0x38];
    FRotator Unknown38;
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

void FUN_109672e0(const Struct_10B1DCA0& Coords, const FVector& V, FVector& Out);

// FUNCTION: 0x10B1DD70 ?FUN_10b1dd70@@YA?AVFVector@@PAUStruct_10B1DD70_Param@@@Z
FVector FUN_10b1dd70(Struct_10B1DD70_Param* A)
{
    Struct_10B1DCA0 Coords(FVector(0.0f, 0.0f, 0.0f));
    Coords.FUN_109620b0(A->Unknown38);
    FVector Result;
    FVector V(1.0f, 0.0f, 0.0f);
    FUN_109672e0(Coords, V, Result);
    return Result;
}
