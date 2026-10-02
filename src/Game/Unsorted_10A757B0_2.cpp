// Game/Unsorted_10A757B0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6BBE8;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Class_10E6BBE8* A, int B, int C, int D);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E6BBE8
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(int A, int B, int C, int D);
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void FUN_10a757b0(int A);
};

// FUNCTION: 0x10A757B0 ?FUN_10a757b0@Class_10E6BBE8@@UAEXH@Z
void Class_10E6BBE8::FUN_10a757b0(int A)
{
    Virtual5(A, 0, 1, 0);
    DAT_10f46da0->Virtual1(this, 0x20, A, -1);
}
