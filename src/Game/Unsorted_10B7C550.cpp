// Game/Unsorted_10B7C550.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

extern float DAT_11006e34;

// FUNCTION: 0x10B7C550 ?FUN_10b7c550@@YA?AVFVector@@PBV1@@Z
FVector FUN_10b7c550(const FVector* V)
{
    return FVector(V->X, V->Y, V->Z) * DAT_11006e34;
}
