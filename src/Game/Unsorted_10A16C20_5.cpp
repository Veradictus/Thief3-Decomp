// Game/Unsorted_10A16C20_5.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A15B20
{
public:
    bool FUN_10a15b20(int* A);
    void FUN_10a16270(int* A);
};

class Class_10E5D688
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
    virtual void FUN_10a16f70(int A);

    char Unknown04[4];
    Class_10A15B20 Unknown08;
};

// FUNCTION: 0x10A16F70 ?FUN_10a16f70@Class_10E5D688@@UAEXH@Z
void Class_10E5D688::FUN_10a16f70(int A)
{
    int Key = A;
    if (Unknown08.FUN_10a15b20(&Key))
        Unknown08.FUN_10a16270(&Key);
}
