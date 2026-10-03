// Game/Unsorted_10C2F340_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class FCoords
{
public:
    FCoords& FUN_10961af0(const FRotator& Rot);

    FVector Origin;
    FVector XAxis;
    FVector YAxis;
    FVector ZAxis;
};

extern FCoords DAT_10f46de8;

class Class_10E9AC80
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void FUN_10c2f430(const FRotator& Rotation, float A, float B);
    virtual void Virtual4(const FVector& Direction, float A, float B);
};

// FUNCTION: 0x10C2F430 ?FUN_10c2f430@Class_10E9AC80@@UAEXABVFRotator@@MM@Z
void Class_10E9AC80::FUN_10c2f430(const FRotator& Rotation, float A, float B)
{
    FCoords Coords = FCoords(DAT_10f46de8).FUN_10961af0(Rotation);
    FVector Direction = Coords.XAxis;
    Virtual4(Direction, A, B);
}
