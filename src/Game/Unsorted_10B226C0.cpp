// Game/Unsorted_10B226C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B3ED20
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int Virtual4();
};

struct Struct_10F02BBC
{
    bool Unknown00;
    char Unknown01[7];
};

extern Struct_10F02BBC DAT_10f02bbc[];

class Class_10B228A0
{
public:
    int FUN_10b228a0();

    char Unknown00[0x90];
    Class_10B3ED20* Unknown90;
    Class_10B3ED20* Unknown94;
};

// FUNCTION: 0x10B228A0 ?FUN_10b228a0@Class_10B228A0@@QAEHXZ
int Class_10B228A0::FUN_10b228a0()
{
    if (DAT_10f02bbc[Unknown90->Virtual4()].Unknown00 && DAT_10f02bbc[Unknown94->Virtual4()].Unknown00)
        return 1;
    return 0;
}
