// Game/Unsorted_1094E3E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1094E620_Unknown08
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
    virtual void __stdcall Virtual12();
};

struct Struct_1094E620_Item
{
    int Unknown00;
    int Unknown04;
    Class_1094E620_Unknown08* Unknown08;
};

struct Struct_1094E620_Group
{
    char Unknown00[0x10];
    Struct_1094E620_Item* Unknown10;
    int Unknown14;
    char Unknown18[0x10];
};

class Class_1094E620
{
public:
    void FUN_1094e620(int A, int B);

    char Unknown00[0x108];
    Struct_1094E620_Group* Unknown108;
};

class Object_1094E5D0
{
public:
    virtual int __stdcall Virtual0();
    virtual int __stdcall Virtual1();
    virtual int __stdcall Virtual2();
    virtual int __stdcall Virtual3();
    virtual int __stdcall Virtual4();
    virtual int __stdcall Virtual5();
    virtual int __stdcall Virtual6();
    virtual int __stdcall Virtual7();
    virtual int __stdcall Virtual8();
    virtual int __stdcall Virtual9();
    virtual int __stdcall Virtual10();
    virtual int __stdcall Virtual11(int A, int B, int* C, int D);
};

struct Struct_1094E5D0_Item
{
    char Unknown00[8];
    Object_1094E5D0* Unknown08;
};

struct Struct_1094E7A0
{
    char Unknown00[0x10];
    Struct_1094E5D0_Item* Unknown10;
    int Unknown14;
    char Unknown18[8];
    int Unknown20;
    int Unknown24;
};

class Class_1094E7A0
{
public:
    int FUN_1094e5d0(int A, int B);

    char Unknown00[0x108];
    Struct_1094E7A0* Unknown108;
};

// FUNCTION: 0x1094E5D0 ?FUN_1094e5d0@Class_1094E7A0@@QAEHHH@Z
int Class_1094E7A0::FUN_1094e5d0(int A, int B)
{
    int Result = 0;
    Struct_1094E7A0* Slot = &Unknown108[A];
    if (B < Slot->Unknown14)
    {
        Struct_1094E5D0_Item* Item = &Slot->Unknown10[B];
        if (Item->Unknown08->Virtual11(0, 0, &Result, 0) < 0)
            return 0;
    }
    return Result;
}

// FUNCTION: 0x1094E620 ?FUN_1094e620@Class_1094E620@@QAEXHH@Z
void Class_1094E620::FUN_1094e620(int A, int B)
{
    Struct_1094E620_Group* Group = &Unknown108[A];
    if (B < Group->Unknown14)
        Group->Unknown10[B].Unknown08->Virtual12();
}
