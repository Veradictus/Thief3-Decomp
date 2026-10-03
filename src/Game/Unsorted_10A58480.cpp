// Game/Unsorted_10A58480.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10A58490
{
public:
    void FUN_10a58490(const FVector& A);

    char Unknown00[0x10];
    FVector Unknown10;
    FVector Unknown1C;
    FVector Unknown28;
};

// FUNCTION: 0x10A58490 ?FUN_10a58490@Class_10A58490@@QAEXABVFVector@@@Z
void Class_10A58490::FUN_10a58490(const FVector& A)
{
    Unknown1C = A;
    Unknown28 = Unknown1C - Unknown10;
}
