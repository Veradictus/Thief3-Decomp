// Game/Unsorted_10C1BEE0_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

extern void* DAT_10e98f48[];

class Class_10C1B840
{
public:
    Class_10C1B840(int A, int B, int C, int D, int E, float F);

    void** Unknown00;
    int Unknown04[17];
};

class Class_10E98F48 : public Class_10C1B840
{
public:
    Class_10E98F48* FUN_10c1bee0(int A, FVector* B, int C, UObject* D, int E, float F, float G);

    FVector Unknown48;
    UObject* Unknown54;
};

// FUNCTION: 0x10C1BEE0 ?FUN_10c1bee0@Class_10E98F48@@QAEPAV1@HPAVFVector@@HPAVUObject@@HMM@Z
Class_10E98F48* Class_10E98F48::FUN_10c1bee0(int A, FVector* B, int C, UObject* D, int E, float F, float G)
{
    this->Class_10C1B840::Class_10C1B840(A, C, E, (int)F, (int)G, 1.0f);
    Unknown00 = DAT_10e98f48;
    Unknown48 = *B;
    Unknown54 = D;
    return this;
}
