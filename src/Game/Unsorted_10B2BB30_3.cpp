// Game/Unsorted_10B2BB30_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10B2BC90_Unknown
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
    virtual FVector* Virtual8();
};

class Class_10A52EE0
{
public:
    Class_10B2BC90_Unknown* FUN_10a52ee0(int A);
};

class Class_10B2BC90 : public Class_10A52EE0
{
public:
    FVector FUN_10b2bc90(int Index);

    char Unknown00[0x128];
    int Unknown128[4];
};

// FUNCTION: 0x10B2BC90 ?FUN_10b2bc90@Class_10B2BC90@@QAE?AVFVector@@H@Z
FVector Class_10B2BC90::FUN_10b2bc90(int Index)
{
    Class_10B2BC90_Unknown* Obj = FUN_10a52ee0(Unknown128[Index]);
    if (Obj)
        return *Obj->Virtual8();
    return FVector(0, 0, 0);
}
