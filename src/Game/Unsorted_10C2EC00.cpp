// Game/Unsorted_10C2EC00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_109BC840
{
public:
    void FUN_109bc160(int A, FVector* Out);
};

class Class_10BAA580
{
public:
    Class_109BC840* FUN_10baa580();
};

class Class_10E9AC80
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
    virtual void Virtual15();
    virtual void Virtual16();
    virtual FVector FUN_10c2ec90(int A);

    char Unknown04[4];
    Class_10BAA580* Unknown08;
};

// FUNCTION: 0x10C2EC90 ?FUN_10c2ec90@Class_10E9AC80@@UAE?AVFVector@@H@Z
FVector Class_10E9AC80::FUN_10c2ec90(int A)
{
    FVector Result(0.0f, 0.0f, 0.0f);
    Unknown08->FUN_10baa580()->FUN_109bc160(A, &Result);
    return Result;
}
