// Game/Unsorted_1094EA10.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9(int A, int B);
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void FUN_1094eab0();

    char Unknown04[0x104];
    Class_Field108* Unknown108;
    char Unknown10C[4];
    int Unknown110;
};

// FUNCTION: 0x1094EAB0 ?FUN_1094eab0@Class_10E4AB88@@UAEXXZ
void Class_10E4AB88::FUN_1094eab0()
{
    Virtual8();
    int Count = Unknown108[Unknown110].Unknown14;
    for (int i = 0; i < Count; i++)
        Virtual9(0, i);
}
