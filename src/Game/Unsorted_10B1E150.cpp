// Game/Unsorted_10B1E150.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

extern float DAT_10e49684;

// FUNCTION: 0x10B1E2E0 ?FUN_10b1e2e0@@YAMMM@Z
float FUN_10b1e2e0(float A, float B)
{
    FVector V;
    V = FVector(A, B, 0.0f);
    V.Normalize();
    float R = V.Y * B;
    R += V.X * A;
    return (R > DAT_10e49684) ? DAT_10e49684 : R;
}
