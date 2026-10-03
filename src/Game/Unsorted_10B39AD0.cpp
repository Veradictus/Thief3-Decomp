// Game/Unsorted_10B39AD0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

struct Struct_109B2D20 : public FVector
{
    using FVector::operator=;
};

class Class_109B2D20
{
public:
    Struct_109B2D20 FUN_109b2d20();
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

struct Struct_10B39B30_Param
{
    char Unknown00[0x38];
    FRotator Unknown38;
};

// FUNCTION: 0x10B39B30 ?FUN_10b39b30@@YGMPAUStruct_10B39B30_Param@@PAVClass_109B2D20@@@Z
FLOAT __stdcall FUN_10b39b30(Struct_10B39B30_Param* A, Class_109B2D20* B)
{
    Struct_109B2D20 V = B->FUN_109b2d20();
    Struct_10B1DCA0 Coords(FVector(0.0f, 0.0f, 0.0f));
    Coords.FUN_109620b0(FRotator(A->Unknown38));
    {
        FVector Result;
        FUN_109672e0(Coords, V, Result);
        V = Result;
    }
    return V.Z;
}
