// Game/Unsorted_10A3A660.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10E66718
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual FVector FUN_10a3a950();

    char Unknown04[0x110];
    FVector Unknown114;
    FVector Unknown120;
};

// FUNCTION: 0x10A3A950 ?FUN_10a3a950@Class_10E66718@@UAE?AVFVector@@XZ
FVector Class_10E66718::FUN_10a3a950()
{
    FVector Result = (Unknown120 + Unknown114) * 0.5f;
    return Result;
}
