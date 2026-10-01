// Game/Unsorted_10C04DC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

float FUN_10c054b0(float A, float B, float C, float D, float E);

struct Struct_10C05A50
{
    float Unknown00;
    float Unknown04;
};

float FUN_10c05a50(const Struct_10C05A50* A, const Struct_10C05A50* B);

int FUN_109688a0(int A, int B, int C);

// FUNCTION: 0x10C054B0 ?FUN_10c054b0@@YAMMMMMM@Z
float FUN_10c054b0(float A, float B, float C, float D, float E)
{
    float Slope = (E - C) / (D - B);
    return Slope * A + (C - B * Slope);
}

// FUNCTION: 0x10C055D0 ?FUN_10c055d0@@YA?AVFVector@@PBV1@@Z
FVector FUN_10c055d0(const FVector* V)
{
    return FVector(V->Y, -V->X, V->Z);
}

// FUNCTION: 0x10C05A50 ?FUN_10c05a50@@YAMPBUStruct_10C05A50@@0@Z
float FUN_10c05a50(const Struct_10C05A50* A, const Struct_10C05A50* B)
{
    float X = B->Unknown00 - A->Unknown00;
    float Y = B->Unknown04 - A->Unknown04;
    return X * X + Y * Y;
}

// FUNCTION: 0x10C061A0 ?FUN_10c061a0@@YA_NHHH@Z
bool FUN_10c061a0(int A, int B, int C)
{
    return FUN_109688a0(A, B, C) != 0;
}
