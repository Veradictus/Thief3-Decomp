// Game/Unsorted_10A64E40.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class FBox
{
public:
    FBox(const FVector& InMin, const FVector& InMax) : Min(InMin), Max(InMax), IsValid(1) {}

    FVector Min;
    FVector Max;
    BYTE IsValid;
};

class Class_10E68B10
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual FBox FUN_10a64e40();

    char Unknown04[0x30];
    FLOAT Unknown34;
    FLOAT Unknown38;
};

// FUNCTION: 0x10A64E40 ?FUN_10a64e40@Class_10E68B10@@UAE?AVFBox@@XZ
FBox Class_10E68B10::FUN_10a64e40()
{
    return FBox(FVector(0.0f, Unknown38, 0.0f), FVector(Unknown34, 0.0f, 0.0f));
}
