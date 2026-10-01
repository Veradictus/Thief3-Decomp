// Game/Unsorted_10A757B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6BBE8;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3(Class_10E6BBE8* A, int B, int C, int D);
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
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7(int A);
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void FUN_10a757e0(int A);
};

// FUNCTION: 0x10A757E0 ?FUN_10a757e0@Class_10E6BBE8@@UAEXH@Z
void Class_10E6BBE8::FUN_10a757e0(int A)
{
    Virtual7(A);
    DAT_10f46da0->Virtual3(this, 0x20, A, -1);
}
