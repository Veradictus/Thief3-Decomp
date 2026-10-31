// Game/GridDirectionAngle.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10B056C0
{
public:
    FRotator* FUN_10b056c0(FRotator& Out) const;
};

static inline FRotator RotationDifference(const FRotator& Current, const FRotator& Desired)
{
    FRotator Result;
    Result.Pitch = Current.Pitch - Desired.Pitch;
    Result.Yaw = Current.Yaw - Desired.Yaw;
    Result.Roll = Current.Roll - Desired.Roll;
    return Result;
}

// FUNCTION: 0x10C05B50 ?FUN_10c05b50@@YA?AVFRotator@@PBVFVector@@PBV1@0@Z
FRotator FUN_10c05b50(const FVector* Origin, const FRotator* Current, const FVector* Target)
{
    FVector Direction = *Target - *Origin;
    FRotator Rotation;
    FRotator* Desired = ((const Class_10B056C0*)&Direction)->FUN_10b056c0(Rotation);
    FRotator Result = RotationDifference(*Current, *Desired);
    Result.Yaw &= 0xffff;
    return Result;
}
