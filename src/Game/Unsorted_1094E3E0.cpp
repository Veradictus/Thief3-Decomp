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

// FUNCTION: 0x1094E620 ?FUN_1094e620@Class_1094E620@@QAEXHH@Z
void Class_1094E620::FUN_1094e620(int A, int B)
{
    Struct_1094E620_Group* Group = &Unknown108[A];
    if (B < Group->Unknown14)
        Group->Unknown10[B].Unknown08->Virtual12();
}
