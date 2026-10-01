// Game/Unsorted_1094E7A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_Field108
{
public:
    char Unknown00[0x14];
    int Unknown14;
    char Unknown18[0x10];
};

class Class_10E4AB88
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual int FUN_1094e800();

    char Unknown04[0x104];
    Class_Field108* Unknown108;
    char Unknown10C[4];
    int Unknown110;
};

extern int DAT_10f2c720;

class Class_1094E7A0_Unknown114
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual int Virtual6(int A, int B, int* C);
};

struct Struct_1094E7A0
{
    char Unknown00[0x20];
    int Unknown20;
    int Unknown24;
};

class Class_1094E7A0
{
public:
    int FUN_1094e7a0(int A);

    char Unknown00[0x108];
    Struct_1094E7A0* Unknown108;
    int Unknown10C;
    int Unknown110;
    Class_1094E7A0_Unknown114* Unknown114[1];
};

// FUNCTION: 0x1094E7A0 ?FUN_1094e7a0@Class_1094E7A0@@QAEHH@Z
int Class_1094E7A0::FUN_1094e7a0(int A)
{
    int Result = 0;
    if (Unknown114[DAT_10f2c720])
    {
        int Handle = Unknown108[Unknown110].Unknown20;
        if (Unknown114[DAT_10f2c720]->Virtual6(0, Handle, &Result) < 0)
            return 0;
    }
    return Result;
}

// FUNCTION: 0x1094E800 ?FUN_1094e800@Class_10E4AB88@@UAEHXZ
int Class_10E4AB88::FUN_1094e800()
{
    return Unknown108[Unknown110].Unknown14;
}
