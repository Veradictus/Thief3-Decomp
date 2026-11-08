// Game/GridBoxCorners.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/CoreClasses.h"

// FUNCTION: 0x10C20A50 ?FUN_10c20a50@@YAXPBUFBox@@PAVFVector@@@Z
void FUN_10c20a50(const FBox* Box, FVector* Corners)
{
    Corners[0] = FVector(Box->Min.X, Box->Min.Y, Box->Min.Z);
    Corners[1] = FVector(Box->Min.X, Box->Min.Y, Box->Max.Z);
    Corners[2] = FVector(Box->Min.X, Box->Max.Y, Box->Max.Z);
    Corners[3] = FVector(Box->Min.X, Box->Max.Y, Box->Min.Z);
    Corners[4] = FVector(Box->Max.X, Box->Min.Y, Box->Min.Z);
    Corners[5] = FVector(Box->Max.X, Box->Min.Y, Box->Max.Z);
    Corners[6] = FVector(Box->Max.X, Box->Max.Y, Box->Max.Z);
    Corners[7] = FVector(Box->Max.X, Box->Max.Y, Box->Min.Z);
}
