// Game/Unsorted_10B3C760.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

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

class Class_10B39890
{
public:
    void* FUN_10b39890(int A);
};

struct Struct_10B3C760_Param
{
    char Unknown00[0x38];
    FRotator Unknown38;
};

class Class_10B3C760
{
public:
    bool FUN_10b3c430(Struct_10B3C760_Param* A, const FVector& V, bool C);
    bool FUN_10b3c760(Struct_10B3C760_Param* A, int Index, bool C);

    char Unknown00[0xC];
    Class_10B39890* Unknown0C;
};

// FUNCTION: 0x10B3C760 ?FUN_10b3c760@Class_10B3C760@@QAE_NPAUStruct_10B3C760_Param@@H_N@Z
bool Class_10B3C760::FUN_10b3c760(Struct_10B3C760_Param* A, int Index, bool C)
{
    FVector V = *(FVector*)Unknown0C->FUN_10b39890(Index);
    Struct_10B1DCA0 Coords(FVector(0.0f, 0.0f, 0.0f));
    Coords.FUN_109620b0(A->Unknown38);
    {
        FVector Result;
        FUN_109672e0(Coords, V, Result);
        V = Result;
    }
    return FUN_10b3c430(A, V, C);
}
