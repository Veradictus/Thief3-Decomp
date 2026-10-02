// Game/Unsorted_10A4EB60_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(int A, int B, int C, int D, int E);
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* Block);
};

Class_10905A90_Member* FUN_10905aa0();

class Class_10A4EFB0
{
public:
    void FUN_10a4e9d0(int Count);
    void FUN_10a4efb0();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

class Class_10BB7C00
{
public:
    void FUN_10bb7c00();

    FString Unknown00;
    char Unknown0C[0x10];
};

class Class_10AF4BB0
{
public:
    void FUN_10af3b50(int A);

    void* Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10A4FC00 : public Class_10AF4BB0
{
public:
    void FUN_10a4fc00(int Slack);
    void FUN_10a4fc50(int Index, int Count);
};

// FUNCTION: 0x10A4EFB0 ?FUN_10a4efb0@Class_10A4EFB0@@QAEXXZ
void Class_10A4EFB0::FUN_10a4efb0()
{
    FUN_10a4e9d0(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}

// FUNCTION: 0x10A4FC00 ?FUN_10a4fc00@Class_10A4FC00@@QAEXH@Z
void Class_10A4FC00::FUN_10a4fc00(int Slack)
{
    for (int i = 0; i < Unknown04; i++)
        ((Class_10BB7C00*)Unknown00)[i].FUN_10bb7c00();
    Unknown04 = 0;
    Unknown08 = Slack;
    FUN_10af3b50(0x1c);
}
