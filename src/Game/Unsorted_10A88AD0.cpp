// Game/Unsorted_10A88AD0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10A88D00
{
public:
    float FUN_10a889e0(float X, float Y);
    float FUN_10a88ad0(int B, FVector* Dir, int C);
    float FUN_10a88d00(FVector* A, int B, int C);
};

// FUNCTION: 0x10A88D00 ?FUN_10a88d00@Class_10A88D00@@QAEMPAVFVector@@HH@Z
float Class_10A88D00::FUN_10a88d00(FVector* A, int B, int C)
{
    float Scale = FUN_10a889e0(A->X, A->Y);
    A->Normalize();
    return FUN_10a88ad0(B, A, C) * Scale;
}
