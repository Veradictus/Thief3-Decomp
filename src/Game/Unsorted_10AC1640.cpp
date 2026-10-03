// Game/Unsorted_10AC1640.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10AC1640_Object
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual bool Virtual5();
};

class Class_10A37860
{
public:
    virtual void Virtual0();

    bool FUN_10a37860();
};

class Class_10A37810 : public Class_10A37860
{
public:
    int FUN_10a37810();
};

struct Struct_10AC14A0
{
    char Unknown00[0x14];
    FRotator Unknown14;
};

class Class_10E6F910 : public Class_10A37810
{
public:
    virtual void Virtual1();
    virtual bool FUN_10ac1640();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void FUN_10ac14a0(const FRotator& R);

    char Unknown04[8];
    FRotator Unknown0C;
    char Unknown18[0x20];
    FRotator Unknown38;
    char Unknown44[0x5BC];
    Struct_10AC14A0* Unknown600;
};

// FUNCTION: 0x10AC1640 ?FUN_10ac1640@Class_10E6F910@@UAE_NXZ
bool Class_10E6F910::FUN_10ac1640()
{
    if (FUN_10a37810())
        return ((Class_10AC1640_Object*)FUN_10a37810())->Virtual5() || FUN_10a37860();
    return FUN_10a37860();
}
