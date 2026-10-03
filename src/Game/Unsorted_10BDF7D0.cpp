// Game/Unsorted_10BDF7D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Engine/EngineClasses.h"

class Class_109BC840
{
public:
    void FUN_109b2920(int A, float B);
};

class Class_10c7d570
{
public:
    void* FUN_10c7d570();
};

class Class_10BAA580 : public Class_10c7d570
{
public:
    Class_109BC840* FUN_10baa580();
};

struct Struct_10BDF7D0
{
    char Unknown00[8];
    Class_10BAA580* Unknown08;
};

class Class_10E955F0
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
    virtual void Virtual17();
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void FUN_10bdf7d0();

    Struct_10BDF7D0* Unknown04;
};

// FUNCTION: 0x10BDF7D0 ?FUN_10bdf7d0@Class_10E955F0@@UAEXXZ
void Class_10E955F0::FUN_10bdf7d0()
{
    ((APawn*)Unknown04->Unknown08->FUN_10c7d570())->IsBlinded = 0;
    if (Unknown04->Unknown08->FUN_10baa580())
        Unknown04->Unknown08->FUN_10baa580()->FUN_109b2920(0, 1.0f);
}
