// Game/Unsorted_10B3AF60_4.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10B48890
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
    virtual void Virtual18(int A, int B, int C);

    char Unknown04[0x1C];
    FVector Unknown20;
    FVector Unknown2C;
};

class Class_10B3AF40_UnknownB0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual Class_10B48890* Virtual6();
};

class AGarrett
{
public:
    char Unknown00[0xB0];
    Class_10B3AF40_UnknownB0* m_physicsObjectPadding;
};

class Class_10E7E658
{
public:
    void FUN_10b3b030(AGarrett* Garrett);
};

// FUNCTION: 0x10B3B030 ?FUN_10b3b030@Class_10E7E658@@QAEXPAVAGarrett@@@Z
void Class_10E7E658::FUN_10b3b030(AGarrett* Garrett)
{
    Class_10B48890* Body = Garrett->m_physicsObjectPadding->Virtual6();
    Body->Unknown20 = FVector(0.0f, 0.0f, 0.0f);
    Body->Unknown2C = FVector(0.0f, 0.0f, 0.0f);
    Body->Virtual18(8, 1, 0);
}
